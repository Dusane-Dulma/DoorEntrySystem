#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <ctime>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

string currentTime();
bool Cleaningtime(const string& startTimeStr, const string& endTimeStr);


namespace doorentrytest
{
	TEST_CLASS(doorentrytest) {
public: TEST_METHOD(TestWithinTimeslot) 
{ // Arrange 
	string startTime = "00:00 am";
	string endTime = "11:00 pm"; 
	// Act 
	bool result = Cleaningtime(startTime, endTime); 
	//Assert
	Assert::IsTrue(result, L"Current time should be within the timeslot."); 
} 
	  
	  TEST_METHOD(TestOutsideTimeslot) 
	  { 
		  // Arrange 
		   string startTime = "1:00 pm"; 
		   string endTime = "3:00 pm"; 
		   // Act 
		   bool result = Cleaningtime(startTime, endTime); 
		   // Assert 
		   Assert::IsFalse(result, L"Current time should be outside the timeslot."); 
	  } 
	  
	  TEST_METHOD(TestBoundaryTimeslot) 
	  { 
		  // Arrange 
		  string startTime = "10:00 am"; 
		  string endTime = "11:59 pm"; 
		  // Act 
		  bool result = Cleaningtime(startTime, endTime); 
		  // Assert
		  Assert::IsTrue(result, L"Current time should be within the cleaning timeslot."); 
	  } 


	  TEST_METHOD(TestCleaningtime)
	  { // Test example times 
		  string startTime = "11:00 AM";
		  string endTime = "14:59 PM";
		  // Act
		  bool testResult = Cleaningtime(startTime, endTime);
		  // Assert 
		  string result = currentTime();
		  wstring assertMessage = L"Test result: " + wstring(result.begin(),result.end());
		  Assert::IsTrue(testResult, assertMessage.c_str());
	  }

	};
}




bool Cleaningtime(const string& startTimeStr, const string& endTimeStr)
{
	tm startTime = {};
	tm endTime = {};
	istringstream ssStartTime(startTimeStr);
	istringstream ssEndTime(endTimeStr);
	ssStartTime >> get_time(&startTime, "%H:%M %p");
	ssEndTime >> get_time(&endTime, "%H:%M %p");
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	tm now_tm;
	localtime_s(&now_tm, &now_time);
	return mktime(&now_tm) >= mktime(&startTime) && mktime(&now_tm) <= mktime(&endTime);
}

string currentTime()
{
	time_t now = time(0);
	tm local_time; localtime_s(&local_time, &now);
	int hour = local_time.tm_hour;
	int minute = local_time.tm_min;
	std::string am_pm = hour >= 12 ? "PM" : "AM";
	// Convert to 12-hour format
	hour = hour % 12; if (hour == 0) hour = 12; // Midnight or Noon 
	// Format the time string 
	char buffer[10];
	sprintf_s(buffer, sizeof(buffer), "%02d:%02d %s", hour, minute, am_pm.c_str());
	return std::string(buffer);
}