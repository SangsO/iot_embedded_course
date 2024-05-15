void MsgSend_adm(int Send_msg)
{
  sprintf(SendMsgData, "[admin]%d\n", Send_msg);
  Serial.println(SendMsgData);
  client.print(SendMsgData);
}

void MsgSend_Jet(char* Send_msg)
{
  sprintf(SendMsgData, "[Jets1]%s\n", Send_msg);
  client.print(SendMsgData);
}
