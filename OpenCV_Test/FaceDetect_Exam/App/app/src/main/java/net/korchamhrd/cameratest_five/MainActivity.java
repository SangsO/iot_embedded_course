package net.korchamhrd.cameratest_five;


import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.annotation.RequiresApi;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v4.content.FileProvider;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    private static final int REQUEST_IMAGE_CAPTURE = 672;
    private String imageFilePath, getip, encode_result, recv_data, all_imageFileName;
    private Uri photoUri;
    private Button btnpic,btncnt, btnsndglass;

    private EditText txtip, txtport;
    private Socket socket;
    private int getport;

    private BufferedReader buf_rd;
    private BufferedWriter buf_wr;
    private PrintWriter out;

    private base64utility test;
    private int check_data = 0, item_num;

    private TextView testview;
    private boolean running = false;
    private int send_wait = 0;

    Thread imgsnd_th;

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        btnpic = (Button)findViewById(R.id.btnpic);
        txtip = (EditText)findViewById(R.id.txtip);
        txtport = (EditText)findViewById(R.id.txtport);
        btncnt = (Button)findViewById(R.id.btncnt);
        btnsndglass = (Button)findViewById(R.id.btnsndglass);
        testview = (TextView)findViewById(R.id.testview);
        test = new base64utility();

////////////////////////////////////////////////////////////////
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE)!= PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.READ_EXTERNAL_STORAGE)) {
                requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,Manifest.permission.ACCESS_FINE_LOCATION,Manifest.permission.ACCESS_COARSE_LOCATION,Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
            } else {
                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.READ_EXTERNAL_STORAGE},
                        1);
            }
            requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,Manifest.permission.ACCESS_FINE_LOCATION,Manifest.permission.ACCESS_COARSE_LOCATION,Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
        }

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)!= PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this,Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,Manifest.permission.ACCESS_FINE_LOCATION,Manifest.permission.ACCESS_COARSE_LOCATION,Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
            } else {
                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},
                        1);
            }
            requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,Manifest.permission.ACCESS_FINE_LOCATION,Manifest.permission.ACCESS_COARSE_LOCATION,Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
        }
///////////////////////////////////////////////////////////////

        btnpic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendTakePhotoIntent();
            }
        });


        btncnt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(txtip.getText().toString().length() == 0 || txtport.getText().toString().length() == 0)
                    return;
                getip = txtip.getText().toString();
                getport =  Integer.parseInt(txtport.getText().toString());
                sockconnect.start();

                imgsnd_th.start();
            }
        });

        btnsndglass.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                item_num = 1;
                send_wait=1;
            }
        });

    }
    @Override
    protected void onResume() {
        super.onResume();

        running = true;
        imgsnd_th = new senddata();
    }

    private void sendTakePhotoIntent(){
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if(takePictureIntent.resolveActivity(getPackageManager())!=null){
            File photoFile = null;
            try{
                photoFile = createImageFile();
            }catch(IOException ex){

            }

            if(photoFile != null){
                photoUri = FileProvider.getUriForFile(this, getPackageName(), photoFile);
                takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);
                startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE);
            }
        }
    }


    private File createImageFile() throws IOException {
        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        String imageFileName = timeStamp + "_";

        File dir = new File(Environment.getExternalStorageDirectory()+"/Pictures/test/");
        if(!dir.exists()){
            dir.mkdirs();
        }

        all_imageFileName = imageFileName+".jpg";
        File storagedir = new File(Environment.getExternalStorageDirectory().getAbsoluteFile()+"/Pictures/test/"+all_imageFileName);
        imageFilePath = storagedir.getAbsolutePath();

        return storagedir;
    }


    class base64utility{
        public Bitmap decode(String encodedImage){
            byte[] decodedString = Base64.decode(encodedImage, Base64.DEFAULT);
            Bitmap decodedByte = BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
            return decodedByte;
        }

        public String encodeJPEG(String imagePath){
            return encode(Bitmap.CompressFormat.JPEG,imagePath);
        }

        private String encode(Bitmap.CompressFormat format, String imagePath){
            Bitmap bitmap = BitmapFactory.decodeFile(imagePath);
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            bitmap.compress(format, 100, baos);
            byte[] byteArrayImage = baos.toByteArray();
            String encodedImaged = Base64.encodeToString(byteArrayImage, Base64.DEFAULT);
            return encodedImaged;
        }

    }

    class senddata extends Thread{
        @Override
        public void run() {
            while(running){
                try{
                    while(send_wait ==0);
                    send_wait = 0;


                    BitmapFactory.Options options = new BitmapFactory.Options();
                    options.inSampleSize = 8;
                    Bitmap orgImage = BitmapFactory.decodeFile(imageFilePath, options);

                    String resize_data = saveBitmaptoJpeg(orgImage, Environment.getExternalStorageDirectory().getAbsoluteFile()+"/Pictures/test/",all_imageFileName );



                    String num = "finish";
                    encode_result = test.encodeJPEG(resize_data);
                    out = new PrintWriter(buf_wr, true);
                    if(item_num == 1)
                    {
                        out.println("1"); //// 1 : 안경 이미지 전송할 것이라고 알림.
                    }
                    while(check_data != 1);
                    check_data = 0;

                    out.println(all_imageFileName); //// 전송 할 이미지 파일 이름.
                    while(check_data != 1);
                    check_data = 0;

                    out.println(String.valueOf(encode_result.length()));
                    while(check_data != 1);
                    check_data = 0;
                    out.println(encode_result);
                    testview.setText(num);



                }catch(Exception ex){

                }
            }
        }
    }

/*
    private Thread senddata = new Thread(){
        @Override
        public void run() {
            try{

                BitmapFactory.Options options = new BitmapFactory.Options();
                options.inSampleSize = 8;
                Bitmap orgImage = BitmapFactory.decodeFile(imageFilePath, options);

                String resize_data = saveBitmaptoJpeg(orgImage, Environment.getExternalStorageDirectory().getAbsoluteFile()+"/Pictures/test/",all_imageFileName );



                String num = "finish";
                encode_result = test.encodeJPEG(resize_data);
                out = new PrintWriter(buf_wr, true);
                if(item_num == 1)
                {
                    out.println("1"); //// 1 : 안경 이미지 전송할 것이라고 알림.
                }
                while(check_data != 1);
                check_data = 0;

                out.println(all_imageFileName); //// 전송 할 이미지 파일 이름.
                while(check_data != 1);
                check_data = 0;

                out.println(String.valueOf(encode_result.length()));
                while(check_data != 1);
                check_data = 0;
                out.println(encode_result);
                testview.setText(num);
            }catch(Exception e){
                e.printStackTrace();
            }
        }
    };
*/
    public static String saveBitmaptoJpeg(Bitmap bitmap,String folder, String name){

        String file_name = name+"_cp.jpg";
        String string_path = folder;

        try{
            FileOutputStream out = new FileOutputStream(string_path+file_name);

            bitmap.compress(Bitmap.CompressFormat.JPEG, 100, out);
            out.close();

        }catch(FileNotFoundException exception){
            Log.e("FileNotFoundException", exception.getMessage());
        }catch(IOException exception){
            Log.e("IOException", exception.getMessage());
        }
        return string_path+file_name;
    }

    private Thread receivedata = new Thread(){
        @Override
        public void run() {
            try{
                while(true){
                    recv_data = buf_rd.readLine();
                    testview.post(new Runnable(){
                        @Override
                        public void run() {
                            check_data = 1;
                        }
                    });
                }
            }catch(Exception e){
                e.printStackTrace();
            }
        }
    };


    private Thread sockconnect = new Thread(){
        @Override
        public void run() {
            try{
                socket = new Socket(getip, getport);
                buf_rd = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                buf_wr = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                receivedata.start();
            }catch(Exception e){
                testview.setText("sockconnect error");
                e.printStackTrace();
            }
        }
    };

}