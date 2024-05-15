
# Smart IoT Electric Charging & Parking Solution
> 전기차 충전소 주차장에 대한 종합 솔루션을 제공
- 진입하는 차량을 인식, 번호판 영상처리를 통해 DB 연동을 통하 전기차 / 내연기관차 및 차량 선별
- 차종에 따른 LCD 안내 및 특정 주차구역으로 안내
- 차량 주차구역 정차 완료 인식될 시 자동 충전 시작
- DB연동 기반 Manipulator 제어로 전기차 충전구 탐색 및 자동 충전
- 영상처리를 통한 Manipulator를 차량 충전구에 정확하게 연결
- 충전기, 차량정보, 충전소 상태 등의 데이터를 서버와 동기화 시켜서 관리 및 Qt GUI 기반 확인 

<img src = "https://user-images.githubusercontent.com/102007930/188815434-24001e1a-2a1f-458c-b9b4-9659e90d7f5c.png" width="510" height="360"/>

## 팀원 및 업무 분담

|이름|내용|
|-----|--------|
|강시형|ROS 통신 기반 구축</br> Pi Camera OpenCV 기반 번호판 인식 및 Realsense 활용 충전구 탐색 구현|
|오규상|OpenCV 기반 충전구탐색 구현</br> Dynamixel 활용 Manipulator 구현</br> 보고서 작성|
|김재현|APM(Apache, php, MariaDB) 및 Socket Server 기반 Qt UI 구현</br>   Arduino Parking System 구현|
|김건우|하드웨어 제작</br>센서, Arduino Parking System 구현|

</br>

## 최종 코드 내용

|이름|내용|
|-----|--------|
|Charge_Manipulator|충전기 Manipulator 동작|
|Blocking_Arduino|입차부 센서 아두이노 코드|
|Blocking_Raspberry|입차부 라즈베리 및 번호판 영상처리 부분|
|Bridge_ros_socket_for_Jetson1|ROS 통신 구축 부분|
|Charge_DepthCamera|충전구 영상처리 코드|
|Mode_Selector|ROS Topic Subscribe 부분|
|QtFinal_Udoo|Qt GUI Socket Server 코드|



</br>

## 업데이트 내역

* 22.09.15
    * 시연 영상 촬영
* 22.09.15
    * 최종 결과보고서 작성 완료
* 22.09.14
    * 하드웨어 조립
* 22.09.09
    * 코드 최적화 및 오류 수정
* 22.09.05
    * Manipulator Bracket 3D 설계 및 인쇄
* 22.08.26
    * 최종 시연용 하드웨어 제작 시작
* 22.08.19
    * 최종 결과보고서 작성 시작
* 22.08.09
    * 개발 내역 정리 및 코드 통합 시작
* 22.07.30
    * Hough Circle 기반 충전구 탐색 알고리즘 마무리 및 KNN Matching 알고리즘 기반 탐색 알고리즘 구현 시작
* 22.07.25
    * Manipulator 기본 탐색 알고리즘 구현 마무리
* 22.07.20
    * Main Server 구축 및 Qt GUI + Socket Server 연동 Tab 구현 마무리
* 22.07.12
    * 중간 결과 개발 진행보고서 작성
* 22.07.10
    * 번호판 알고리즘 Tesseract 적용 및 Manipulator Link Frame 재설계 및 3D Printing 출력
* 22.06.25
    * 번호판 탐색 알고리즘 구현 시작
* 22.06.22
    * 원형 탐색 기반 객체 인식 및 충전구 탐색 알고리즘 
* 22.06.21
    * 차량 3면 탐색 방식 객체 탐색 동작 구현 테스트
* 22.06.17
    * APM 기반 서버 구축 완료 및 Socket 통신 구현. Qt연동 준비
* 22.06.14
    * 색 추적 방식 객체 인식 알고리즘 구현 테스트
* 22.06.05
    * OpenCR 및 Dynamixel 활용 Manipulator 방식 충전기 개발 시작
* 22.06.04
    * OpenCV 기반 충전구 인식 알고리즘 개발 시작
* 22.06.01
    * ROS 환경 구축 시작
* 22.06.01
    * 메인 서버(Raspberry Pi 4 + APM(Apache, php, MariaDB) 개발 및 구축 시작
* 22.05.29
    * 사용자부분 (Qt기반) 개발 시작
* 22.05.29
    * 충전기 Manipulator Hardware 조립
* 22.05.28 ~ 22.06.04 _END
    * 개발환경 구축 완료
* 22.05.26 ~ 22.05.29
    * 개별 업무 분담 및 재료구매 신청 완료
* 22.05.23
    * 아이디어 선정 및 구체화 완료
* 22.05.16
    * 아이디어 주제 탐구

## Workflow
![image](https://user-images.githubusercontent.com/102007930/182278516-c0bf7e28-d8fc-4a0a-8a03-8cc8fa126d42.png)
![image](https://user-images.githubusercontent.com/102007930/182278520-a149a9b3-3583-438b-a753-e7fb2beda625.png)

![image](https://user-images.githubusercontent.com/102007930/188396320-b1916363-c8b5-4de5-b562-d9ebf8532d6b.png)
![image](https://user-images.githubusercontent.com/102007930/188397756-4d23bb93-3a06-47f7-9ee9-fa9adb689ec0.png)





## 기술 스택

| <center>분류</center> |<center>기술 스택</center>|
| :-------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| *Languages*|<img src="https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=C&logoColor=white"/> <img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=C%2B%2B&logoColor=white"/> <img src="https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=Python&logoColor=white"/>|
| *MCU & MPU*|<img src="https://img.shields.io/badge/Raspberry Pi-A22846?style=flat-square&logo=Raspberry Pi&logoColor=white"/> <img src="https://img.shields.io/badge/Jetson Nano-76B900?style=flat-square&logo=NVIDIA&logoColor=white"/> <img src="https://img.shields.io/badge/Arduino-00979D?style=flat-square&logo=Arduino&logoColor=white">|
| *Server / DB*|<img src="https://img.shields.io/badge/Apache-D22128?style=flat-square&logo=Apache&logoColor=white"/> <img src="https://img.shields.io/badge/PHP-777BB4?style=flat-square&logo=PHP&logoColor=white"/> <img src="https://img.shields.io/badge/MySQL-4479A1?style=flat-square&logo=MySQL&logoColor=white"/> |
| *OS*|<img src="https://img.shields.io/badge/Windows 10-0078D6?style=flat-square&logo=Windows&logoColor=white"/> <img src="https://img.shields.io/badge/Ubuntu-E95420?style=flat-square&logo=Ubuntu&logoColor=white"/> |
| *Platform / Library*|<img src="https://img.shields.io/badge/ROS-22314E?style=flat-square&logo=ROS&logoColor=white"/> <img src="https://img.shields.io/badge/OpenCV-5C3EE8?style=flat-square&logo=OpenCV&logoColor=white"/> |
| *VersionControl*|<img src="https://img.shields.io/badge/Git-F05032?style=flat-square&logo=Git&logoColor=white"/> <img src="https://img.shields.io/badge/GitHub-181717?style=flat-square&logo=GitHub&logoColor=white"/> |
| *ETC*|<img src="https://img.shields.io/badge/Google Docs-4285F4?style=flat-square&logo=Google&logoColor=white"/> <img src="https://img.shields.io/badge/Notion-000000?style=flat-square&logo=Notion&logoColor=white"/>|

<!-- Markdown link & img dfn's -->
[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki 
