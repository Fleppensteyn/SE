/*
  SE 2014
  Group 8
*/

#ifndef SERVERCOM_H_
#define SERVERCOM_H_

#include <string>
#include <cstring>
#include "sha1/sha1.h"
#include <curl/curl.h>

class ServerCommunication
{
public:
  //Handles communication with the server
  ServerCommunication(const char * url);

  bool checkLogin(const char * username, const char * password, std::string &mesg);

  bool uploadDatabase(const char * dbname, std::string& mesg);
  void clearLoginData();

private:
  std::string url;
  std::string logindata;

  void sha1Hash(const char * data, char * hash);
};

size_t catch_resp(void * buffer, size_t size, size_t nmemb, void *userp);

#endif /* SERVERCOM_H_ */

