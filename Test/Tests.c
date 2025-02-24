#include "Tests.h"

/************************************************************************************
* Test ID                : defaultTestCase1
* Description            : Testing the Add Account Functionality
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                          Name                         -> Ahmed
*                          Age                          -> 26
*                          DOB_day                      -> 01
*                          DOB_Month                    -> 02
*                          DOB_Year                     -> 1999
*                          Educational_Status           -> Masters_Student
*                          Gender                       -> Male
*                          UserName                     -> EdgesAcademy
*                          Password                     -> Edges123
*                          Password Recheck             -> Edges123
* Test expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : All inputs are in correct format
*************************************************************************************/
static void defaultTestCase1(void)
{
	static struct User_Input_Type defaultTestUser1 = {{-1, "Ahmed", 26, 23, 10, 1998, Male, Masters_Student}, {{"EdgesAcademy", "Edges123"}, "Edges123"}};

	unsigned char RET = Add_Account(&defaultTestUser1);
	defaultTestUser1.PersonalInfo_Form.id = current_user_test - 1;

	if (RET == FALSE)
	{
		CU_ASSERT(FALSE);
	}
	else
	{
		unsigned int Test_id = defaultTestUser1.PersonalInfo_Form.id;
		CU_ASSERT_EQUAL(DB_info[Test_id].Age, defaultTestUser1.PersonalInfo_Form.Age);
		CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, defaultTestUser1.PersonalInfo_Form.DOB_day);
		CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, defaultTestUser1.PersonalInfo_Form.DOB_month);
		CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, defaultTestUser1.PersonalInfo_Form.DOB_year);
		CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, defaultTestUser1.PersonalInfo_Form.educational_status);
		CU_ASSERT_EQUAL(DB_info[Test_id].gender, defaultTestUser1.PersonalInfo_Form.gender);
		CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, defaultTestUser1.PersonalInfo_Form.name);
		CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, defaultTestUser1.LoginCredentials_Form.LoginCredentials.User_Name);
		CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, defaultTestUser1.LoginCredentials_Form.LoginCredentials.Password);
		CU_ASSERT_EQUAL(DB_info[Test_id].id, defaultTestUser1.PersonalInfo_Form.id);

		RET = Delete_Account(defaultTestUser1.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : defaultTestCase2
* Description            : Testing the Add Account Functionality
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                          Name                         -> Rania
*                          Age                          -> 54
*                          DOB_day                      -> 31
*                          DOB_Month                    -> 12
*                          DOB_Year                     -> 1970
*                          Educational_Status           -> PHD_Holder
*                          Gender                       -> Female
*                          UserName                     -> EdgesAcademy2024
*                          Password                     -> Edges_123_$$
*                          Password Recheck             -> Edges123
* Test expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : Password inputs mismatch so the suite willn't initiallize 
*************************************************************************************/

static void defaultTestCase2(void)
{
	static struct User_Input_Type defaultTestUser2 = {{-1, "Rania", 54, 31, 12, 1970, Female, PHD_Holder}, {{"EdgesAcademy2024", "Edges_123_"}, "Edges_123_$$"}};

	unsigned char RET = Add_Account(&defaultTestUser2);
	defaultTestUser2.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET, FALSE);

	/*
	if (RET == TRUE)
	{
		RET = Delete_Account(default_Test_User2.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);
	}*/
}

/************************************************************************************
* Test ID                : TestCase1
* Description            : Try to put more than MAX_USERS(5) users in the DB
* Pre-requisits          : 7 users with valid data Assigned to DB
* Test inputs            : 7 users with valid data (DBM_initDB() already adds 3 users
						   in the DB at the beginning of the program)
* Test expected output   : The function Add_Account() should return FALSE and the DB 
*                          shouldn't be updated with the user's inputs when the DB reaches
*                          it's maximum
* Reason                 : the DB can store and delete users with ID from 0 to 
*                          (MAX_USERS - 1)
*************************************************************************************/
static void testCase1(void)
{
	unsigned char RET;

	static struct User_Input_Type Test_User4 = {{-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"}};
	RET = Add_Account(&Test_User4);
	Test_User4.PersonalInfo_Form.id = current_user_test - 1; /*current_user_test = 4*/
	CU_ASSERT_EQUAL(RET, TRUE);

	static struct User_Input_Type Test_User5 = { {-1, "Jeovany", 26, 22, 1, 1998, Male, PHD_Holder}, {{"Jeo_1234", "12345_jo"}, "12345_jo"} };
	RET = Add_Account(&Test_User5);
	Test_User5.PersonalInfo_Form.id = current_user_test - 1; /*current_user_test = 5*/
	CU_ASSERT_EQUAL(RET, TRUE);


	static struct User_Input_Type Test_User6 = { {-1, "_Mark", 24, 30, 6, 2000, Male, Graduate}, {{"_M34as81", ".Makr123"}, ".Makr123"} };
	RET = Add_Account(&Test_User6);
	Test_User6.PersonalInfo_Form.id = current_user_test - 1; /*current_user_test = 5*/
	CU_ASSERT_EQUAL(RET, FALSE);

	static struct User_Input_Type Test_User7 = { {-1, ".May", 25, 22, 1, 1999, Male, Student}, {{".May12345", "_12345678_"}, "_12345678_"} };
	RET = Add_Account(&Test_User7);
	Test_User7.PersonalInfo_Form.id = current_user_test - 1; /*current_user_test = 5*/
	CU_ASSERT_EQUAL(RET, FALSE);

	/*Delete the first 2 users to make the DB have only the initialized 3 users again*/
	RET = Delete_Account(Test_User5.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(RET, TRUE);

	RET = Delete_Account(Test_User4.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(RET, TRUE);
}

/************************************************************************************
* Test ID                : TestCase2
* Description            : Try to delete user with ID=(MAX_USERS)
* Pre-requisits          : 5 users with valid data Assigned to DB
* Test inputs            : 5 users with valid data (DBM_initDB() already adds 3 users 
                           in the DB at the beginning of the program)
* Test expected output   : The function Delete_Account() should return FALSE
* Reason                 : The DB can store and delete users with ID from 0 to 
*                          (MAX_USERS - 1)
* Test actual output     : The function Delete_Account() returns TRUE, which means it
*                          worked successfully and it maybe deleted a wrong user (in case the DB
*                          is full)
*************************************************************************************/
static void testCase2(void)
{
	unsigned char RET;

	static struct User_Input_Type Test_User4 = { {-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	RET = Add_Account(&Test_User4);
	Test_User4.PersonalInfo_Form.id = current_user_test - 1; /*current_user_test = 4*/

	static struct User_Input_Type Test_User5 = { {-1, "Jeovany", 26, 22, 1, 1998, Female, PHD_Holder}, {{"Jeo_1234", "12345_jo"}, "12345_jo"} };
	RET = Add_Account(&Test_User5);
	Test_User5.PersonalInfo_Form.id = current_user_test - 1; /*current_user_test = 5*/

	RET = Delete_Account(MAX_USERS);
	
	CU_ASSERT_EQUAL(RET, FALSE);
	CU_ASSERT_EQUAL(DB_info[Test_User5.PersonalInfo_Form.id].Age, Test_User5.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(DB_info[Test_User5.PersonalInfo_Form.id].DOB_day, Test_User5.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(DB_info[Test_User5.PersonalInfo_Form.id].DOB_month, Test_User5.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(DB_info[Test_User5.PersonalInfo_Form.id].DOB_year, Test_User5.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(DB_info[Test_User5.PersonalInfo_Form.id].educational_status, Test_User5.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(DB_info[Test_User5.PersonalInfo_Form.id].gender, Test_User5.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(DB_info[Test_User5.PersonalInfo_Form.id].name, Test_User5.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_User5.PersonalInfo_Form.id].User_Name, Test_User5.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_User5.PersonalInfo_Form.id].Password, Test_User5.LoginCredentials_Form.LoginCredentials.Password);
}

/************************************************************************************
* Test ID                : TestCase3
* Description            : Try to put a anything not letters in the name parameter in
*                          the Add_Account() function
* Pre-requisits          : Assign a user to the DB with the name parameter not letters
* Test inputs            : A user to the DB with the name parameter not letters but the
*                          other parameter must be valid
* Test expected output   : The DB shouldn't be updated with the previous inputs and the
*                          function Add_Account() must return FALSE
* Reason                 : The name should be only letters
* Test actual output     : The function Add_Account() returns TRUE, which means it
*                          worked successfully
*************************************************************************************/
static void testCase3(void)
{
	unsigned char RET;
	static struct User_Input_Type Test_User = { {-1, "56324", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	RET = Add_Account(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET, FALSE);
	if (TRUE == RET)
	{
		RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase4
* Description            : Assign a young user to the DB and put his educational_status
*                          to be PHD_Holder
* Pre-requisits          : Assign a user to the DB with age parameter = 8 the educational_status
*                          parameter to be PHD_Holder 
* Test inputs            : A user to the DB with the age parameter = 8 the educational_status
 *                         parameter to be PHD_Holder 
* Test expected output   : The DB shouldn't be updated with the previous inputs and the
*                          function Add_Account() must return FALSE
* Reason                 : The person is too young to have be a PHD_Holder
* Test actual output     : The function Add_Account() returns TRUE, which means it
*                          worked successfully
*************************************************************************************/
static void testCase4(void)
{
	unsigned char RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 8, 18, 10, 2016, Male, PHD_Holder}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	RET = Add_Account(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET, FALSE);
	if (TRUE == RET)
	{
		RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase5
* Description            : Testing user with educational_status = "PHD_Student"
* Pre-requisits          : A user with valid data and educational_status = "PHD_Student" 
*                          assigned in the DB
* Test inputs            : A used with valid data and educational_status = "PHD_Student"
* Test expected output   : When the user data printed, The educational_status should be
*                          "PHD_Student"
* Test actual output     : The user educational_status that be printed is "THURSDAY"
* Status                 : Failed
*************************************************************************************/
static void testCase5(void)
{
	unsigned char RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 24, 18, 10, 2000, Male, PHD_Student}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	RET = Add_Account(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;

	if (RET == FALSE)
	{
		CU_ASSERT(FALSE);
	}
	else
	{
		RET = DBM_PrintUserData_Admin(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);

		RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase6
* Description            : 
* Pre-requisits          : 
* Test inputs            : 
* Test expected output   : 
* Reason                 : 
* Test actual output     : 
*************************************************************************************/
/*
static void TestCase6(void)
{

}
*/
/************************************************************************************
* Test ID                : TestCase7
* Description            : Test the boundaries for the user_id input of the function
*                          ShowStudentCourses() in course_reg module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (0)
* Test expected output   : The function should print the courses the user enrolled in
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase7(void)
{
	ShowStudentCourses(0);
}

/************************************************************************************
* Test ID                : TestCase8
* Description            : Test the boundaries for the user_id input of the function
*                          ShowStudentCourses() in course_reg module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (1)
* Test expected output   : The function should print the courses the user enrolled in
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase8(void)
{
	ShowStudentCourses(1);
}

/************************************************************************************
* Test ID                : TestCase9
* Description            : Test the boundaries for the user_id input of the function
*                          ShowStudentCourses() in course_reg module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (MAX_USERS-1)
* Test expected output   : The function should print the courses the user enrolled in
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase9(void)
{
	ShowStudentCourses(MAX_USERS-1);
}

/************************************************************************************
* Test ID                : TestCase10
* Description            : Test the boundaries for the user_id input of the function
*                          ShowStudentCourses() in course_reg module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (-1)
* Test expected output   : The function should print "Invalid User Id"
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase10(void)
{
	ShowStudentCourses(-1);
}

/************************************************************************************
* Test ID                : TestCase11
* Description            : Test the boundaries for the user_id input of the function
*                          ShowStudentCourses() in course_reg module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS)
* Test expected output   : The function should print "Invalid User Id"
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase11(void)
{
	ShowStudentCourses(MAX_USERS);
}

/************************************************************************************
* Test ID                : TestCase12
* Description            : Test the boundaries for the user_id input of the function
*                          ShowStudentCourses() in course_reg module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS+1)
* Test expected output   : The function should print "Invalid User Id"
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase12(void)
{
	ShowStudentCourses(MAX_USERS+1);
}

/************************************************************************************
* Test ID                : TestCase13
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (0)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase13(void)
{
	CU_ASSERT_EQUAL(DBM_Delete_User(0), TRUE);
}

/************************************************************************************
* Test ID                : TestCase14
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (1)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase14(void)
{
	CU_ASSERT_EQUAL(DBM_Delete_User(1), TRUE);
}

/************************************************************************************
* Test ID                : TestCase15
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (MAX_USERS-1)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase15(void)
{
	CU_ASSERT_EQUAL(DBM_Delete_User(MAX_USERS - 1), TRUE);
}

/************************************************************************************
* Test ID                : TestCase16
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (-1)
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase16(void)
{
	CU_ASSERT_EQUAL(DBM_Delete_User(-1), FALSE);
}

/************************************************************************************
* Test ID                : TestCase17
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS)
* Test expected output   : The function should return FALSE
* Test actual output     : The function returned TRUE
* Status                 : Failed
*************************************************************************************/
static void TestCase17(void)
{
	CU_ASSERT_EQUAL(DBM_Delete_User(MAX_USERS), FALSE);
}

/************************************************************************************
* Test ID                : TestCase18
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS+1)
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase18(void)
{
	CU_ASSERT_EQUAL(DBM_Delete_User(MAX_USERS + 1), FALSE);
}

/************************************************************************************
* Test ID                : TestCase19
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_Admin() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (0)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase19(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_Admin(0), TRUE);
}

/************************************************************************************
* Test ID                : TestCase20
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_Admin() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (1)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase20(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_Admin(1), TRUE);
}

/************************************************************************************
* Test ID                : TestCase21
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_Admin() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (MAX_USERS-1)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase21(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_Admin(MAX_USERS - 1), TRUE);
}

/************************************************************************************
* Test ID                : TestCase22
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_Admin() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (-1)
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase22(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_Admin(-1), FALSE);
}

/************************************************************************************
* Test ID                : TestCase23
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_Admin() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS)
* Test expected output   : The function should return FALSE
* Test actual output     : The function returned TRUE
* Status                 : Failed
*************************************************************************************/
static void TestCase23(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_Admin(MAX_USERS), FALSE);
}

/************************************************************************************
* Test ID                : TestCase24
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_Admin() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS+1)
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
* Status                 : Passed
*************************************************************************************/
static void TestCase24(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_Admin(MAX_USERS + 1), FALSE);
}

/************************************************************************************
* Test ID                : TestCase25
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (0)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase25(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_User(0), TRUE);
}

/************************************************************************************
* Test ID                : TestCase26
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (1)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase26(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_User(1), TRUE);
}

/************************************************************************************
* Test ID                : TestCase27
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (MAX_USERS-1)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase27(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_User(MAX_USERS - 1), TRUE);
}

/************************************************************************************
* Test ID                : TestCase28
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (-1)
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase28(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_User(-1), FALSE);
}

/************************************************************************************
* Test ID                : TestCase29
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS)
* Test expected output   : The function should return FALSE
* Test actual output     : The function returned TRUE
* Status                 : Failed
*************************************************************************************/
static void TestCase29(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_User(MAX_USERS), FALSE);
}

/************************************************************************************
* Test ID                : TestCase30
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_PrintUserData_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS+1)
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase30(void)
{
	CU_ASSERT_EQUAL(DBM_PrintUserData_User(MAX_USERS + 1), FALSE);
}

/************************************************************************************
* Test ID                : TestCase31
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (0)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase31(void)
{
	CU_ASSERT_EQUAL(Delete_Account(0), TRUE);
}

/************************************************************************************
* Test ID                : TestCase32
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (1)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase32(void)
{
	CU_ASSERT_EQUAL(Delete_Account(1), TRUE);
}

/************************************************************************************
* Test ID                : TestCase33
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid user_id (MAX_USERS-1)
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase33(void)
{
	CU_ASSERT_EQUAL(Delete_Account(MAX_USERS - 1), TRUE);
}

/************************************************************************************
* Test ID                : TestCase34
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (-1)
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase34(void)
{
	CU_ASSERT_EQUAL(Delete_Account(-1), FALSE);
}

/************************************************************************************
* Test ID                : TestCase35
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS)
* Test expected output   : The function should return FALSE
* Test actual output     : The function returned TRUE
* Status                 : Failed
*************************************************************************************/
static void TestCase35(void)
{
	CU_ASSERT_EQUAL(Delete_Account(MAX_USERS), FALSE);
}

/************************************************************************************
* Test ID                : TestCase36
* Description            : Test the boundaries for the user_id input of the function
*                          DBM_Delete_User() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid user_id (MAX_USERS+1)
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase36(void)
{
	CU_ASSERT_EQUAL(Delete_Account(MAX_USERS + 1), FALSE);
}

/************************************************************************************
* Test ID                : TestCase37
* Description            : Test the boundaries for the user_id and course_id inputs
*                          of the function DBM_AddToCourse() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Valid course_id and invalid user_id
* Test expected output   : The function should return ERROR
* Status                 : Failed
*************************************************************************************/
static void TestCase37(void)
{
	unsigned char RET = DBM_AddToCourse(4, 6);
	CU_ASSERT_EQUAL(RET, ERROR);
}

/************************************************************************************
* Test ID                : TestCase38
* Description            : Test the boundaries for the user_id and course_id inputs
*                          of the function DBM_AddToCourse() in DB_Manager module
* Pre-requisits          : No pre-requisits
* Test inputs            : Invalid course_id and invalid user_id
* Test expected output   : The function should return ERROR
* Status                 : Failed
*************************************************************************************/
static void TestCase38(void)
{
	unsigned char RET = DBM_AddToCourse(8, 8);
	CU_ASSERT_EQUAL(RET, ERROR);
}

/************************************************************************************
* Test ID                : TestCase39
* Description            : Test the condition if(User_ID < 0 || User_ID >= MAX_USERS)
*                          of the function ShowStudentCourses()
* Test Technique         : MC/DC
* Pre-requisits          : No pre-requisits
* Test inputs            : -5
* Test expected output   : The function should print "Invalid User Id"
* Test actual output     : As expected
*************************************************************************************/
static void TestCase39(void)
{
	ShowStudentCourses(-5);
}

/************************************************************************************
* Test ID                : TestCase40
* Description            : Test the condition if(User_ID < 0 || User_ID >= MAX_USERS)
*                          of the function ShowStudentCourses()
* Test Technique         : MC/DC
* Pre-requisits          : No pre-requisits
* Test inputs            : 7
* Test expected output   : The function should print "Invalid User Id"
* Test actual output     : As expected
*************************************************************************************/
static void TestCase40(void)
{
	ShowStudentCourses(7);
}
/************************************************************************************
* Test ID                : TestCase41
* Description            : Test the condition if(User_ID < 0 || User_ID >= MAX_USERS)
*                          of the function ShowStudentCourses()
* Test Technique         : MC/DC
* Pre-requisits          : No pre-requisits
* Test inputs            : 3
* Test expected output   : The function should print "You Are Currently Enrolled in: "
*                          then print the courses the student with this ID enrolled in
* Test actual output     : As expected
*************************************************************************************/
static void TestCase41(void)
{
	ShowStudentCourses(3);
}

/************************************************************************************
* Test ID                : TestCase42
* Description            : Test the nested if condition of the function AddStudentToCourse()
* Test Technique         : Decidion coverage
* Pre-requisits          : There is should be at least 1 empty place in the DB, assign
*                          a user with valid data to the DB and add a course to this user
* Test inputs            : The user_id of the last assigned user and the course_id of the
*                          course added to this user
* Test expected output   : The function should return AlreadyEnrolled;
* Test actual output     : As expected
*************************************************************************************/
static void TestCase42(void)
{
	unsigned char Add_RET, RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 8, 18, 10, 2016, Male, PHD_Holder}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	Add_RET = Add_Account(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(Add_RET, TRUE);

	DBM_AddToCourse(5, Test_User.PersonalInfo_Form.id);
	RET = AddStudentToCourse(5, Test_User.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(RET, AlreadyEnrolled);

	if (TRUE == Add_RET)
	{
		Add_RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(Add_RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase43
* Description            : Test the nested if condition of the function AddStudentToCourse()
* Test Technique         : Decidion coverage
* Pre-requisits          : There is should be at least 1 empty place in the DB, assign
*                          a user with valid data to the DB
* Test inputs            : The user_id of the last assigned user and any course_id
* Test expected output   : The function should return Enrolled;
* Test actual output     : As expected
*************************************************************************************/
static void TestCase43(void)
{
	unsigned char Add_RET, RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 8, 18, 10, 2016, Male, PHD_Holder}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	Add_RET = Add_Account(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(Add_RET, TRUE);

	RET = AddStudentToCourse(5, Test_User.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(RET, Enrolled);

	if (TRUE == Add_RET)
	{
		Add_RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(Add_RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase44
* Description            : Test the nested if condition of the function AddStudentToCourse()
* Test Technique         : Decidion coverage
* Pre-requisits          : Delete all the users in the DB, then assign 5 users with valid
*                          data and assign any course (course_id = 1) to the 5 users
* Test inputs            : Try to assin another user to the same course (course_id = 1)
* Test expected output   : The function should return CapacityCompleted
* Test actual output     : As expected
*************************************************************************************/
static void TestCase44(void)
{
	unsigned char RET, RET1, RET2, RET3, RET4, RET5;
	static struct User_Input_Type Test_User1 = { {-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	static struct User_Input_Type Test_User2 = { {-1, "Jeovany", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	static struct User_Input_Type Test_User3 = { {-1, "Mark", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	static struct User_Input_Type Test_User4 = { {-1, "Steven", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	static struct User_Input_Type Test_User5 = { {-1, "Alice", 24, 18, 10, 2000, Female, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };

	RET = Delete_Account(2);
	CU_ASSERT_EQUAL(RET, TRUE);

	RET = Delete_Account(1);
	CU_ASSERT_EQUAL(RET, TRUE);

	RET = Delete_Account(0);
	CU_ASSERT_EQUAL(RET, TRUE);

	RET1 = DBM_Add_User(&Test_User1);
	Test_User1.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET1, 1);

	RET2 = DBM_Add_User(&Test_User2);
	Test_User2.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET2, 1);

	RET3 = DBM_Add_User(&Test_User3);
	Test_User3.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET3, 1);

	RET4 = DBM_Add_User(&Test_User4);
	Test_User4.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET4, 1);

	RET5 = DBM_Add_User(&Test_User5);
	Test_User5.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET5, 1);

	DBM_AddToCourse(1, Test_User1.PersonalInfo_Form.id);
	DBM_AddToCourse(1, Test_User2.PersonalInfo_Form.id);
	DBM_AddToCourse(1, Test_User3.PersonalInfo_Form.id);
	DBM_AddToCourse(1, Test_User4.PersonalInfo_Form.id);
	DBM_AddToCourse(1, Test_User5.PersonalInfo_Form.id);

	RET = AddStudentToCourse(1, 5);
	CU_ASSERT_EQUAL(RET, CapacityCompleted);

	if (1 == RET1)
	{
		RET1 = Delete_Account(Test_User1.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET1, TRUE);
	}
	if (1 == RET2)
	{
		RET2 = Delete_Account(Test_User2.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET2, TRUE);
	}
	if (1 == RET3)
	{
		RET3 = Delete_Account(Test_User3.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET3, TRUE);
	}
	if (1 == RET4)
	{
		RET4= Delete_Account(Test_User4.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET4, TRUE);
	}
	if (1 == RET5)
	{
		RET5 = Delete_Account(Test_User5.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET5, TRUE);
	}
	DBM_initDB();
}

/************************************************************************************
* Test ID                : TestCase45
* Description            : Test the get_Gender_String() using DBM_PrintUserData_Admin()
* Test Technique         : Decidion coverage
* Pre-requisits          : No pre-requisits
* Test inputs            : A user with valid data (Gender must be "Male")
* Test expected output   : The function print "Male" in the Gender place
* Test actual output     : As expected
*************************************************************************************/
static void TestCase45(void) 
{
	unsigned char RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	RET = Add_Account(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET, TRUE);
	DBM_PrintUserData_Admin(Test_User.PersonalInfo_Form.id);
	if (TRUE == RET)
	{
		RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase46
* Description            : Test the get_Gender_String() using DBM_PrintUserData_Admin()
* Test Technique         : Decidion coverage
* Pre-requisits          : No pre-requisits
* Test inputs            : A user with valid data (Gender must be "Female")
* Test expected output   : The function print "Female" in the Gender place
* Test actual output     : As expected
*************************************************************************************/
static void TestCase46(void)
{
	unsigned char RET;
	static struct User_Input_Type Test_User = { {-1, "Alice", 24, 18, 10, 2000, Female, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	RET = Add_Account(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET, TRUE);

	DBM_PrintUserData_Admin(Test_User.PersonalInfo_Form.id);	
	if (TRUE == RET)
	{
		RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase47
* Description            : Test the get_Gender_String() using DBM_PrintUserData_Admin()
* Test Technique         : Decidion coverage
* Pre-requisits          : No pre-requisits
* Test inputs            : A user_id for an empty place in the DB
* Test expected output   : The function print "default" in the Gender place
* Test actual output     : As expected
*************************************************************************************/
static void TestCase47(void)
{
	DBM_PrintUserData_Admin(4);
}

/************************************************************************************
* Test ID                : TestCase48
* Description            : Test the the condition "if (Current_user == MAX_USERS)" of 
*                          the function DBM_Add_User()
* Test Technique         : Decidion coverage
* Pre-requisits          : The DB should have at least 1 empty place
* Test inputs            : A user with valid data
* Test expected output   : The function should return 1
* Test actual output     : As expected
*************************************************************************************/
static void TestCase48(void)
{
	unsigned char RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	
	RET = DBM_Add_User(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET, 1);

	if (TRUE == RET)
	{
		RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase49
* Description            : Test the the condition "if (Current_user == MAX_USERS)" of
*                          the function DBM_Add_User()
* Test Technique         : Decidion coverage
* Pre-requisits          : The DB should be full (Assign 2 users to the DB) then try to
*                          assign a user to the DB
* Test inputs            : A user with valid data
* Test expected output   : The function should return 0
* Test actual output     : As expected
*************************************************************************************/
static void TestCase49(void)
{
	unsigned char RET1, RET2, RET3;
	static struct User_Input_Type Test_User1 = { {-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	static struct User_Input_Type Test_User2 = { {-1, "Jeovany", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	static struct User_Input_Type Test_User3 = { {-1, "Mark", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };

	RET1 = DBM_Add_User(&Test_User1);
	Test_User1.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET1, 1);

	RET2 = DBM_Add_User(&Test_User2);
	Test_User2.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET2, 1);

	RET3 = DBM_Add_User(&Test_User3);
	Test_User3.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(RET3, 0);

	if (1 == RET1)
	{
		RET1 = Delete_Account(Test_User1.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET1, TRUE);
	}
	if (1 == RET2)
	{
		RET2 = Delete_Account(Test_User2.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET2, TRUE);
	}
	if (1 == RET3)
	{
		RET3 = Delete_Account(Test_User3.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(RET3, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase50
* Description            : Test the condition if(user_id < 0 || user_id > MAX_USERS)
*                          of the function DBM_Delete_User()
* Test Technique         : MC/DC
* Pre-requisits          : No pre-requisits
* Test inputs            : -5
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase50(void)
{
	unsigned char RET = DBM_Delete_User(-5);
	CU_ASSERT_EQUAL(RET, FALSE);
}

/************************************************************************************
* Test ID                : TestCase51
* Description            : Test the condition if(user_id < 0 || user_id > MAX_USERS)
*                          of the function DBM_Delete_User()
* Test Technique         : MC/DC
* Pre-requisits          : No pre-requisits
* Test inputs            : 7
* Test expected output   : The function should return FALSE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase51(void)
{
	unsigned char RET = DBM_Delete_User(7);
	CU_ASSERT_EQUAL(RET, FALSE);
}

/************************************************************************************
* Test ID                : TestCase52
* Description            : Test the condition if(user_id < 0 || user_id > MAX_USERS)
*                          of the function DBM_Delete_User()
* Test Technique         : MC/DC
* Pre-requisits          : There is should be an empty place in the DB and assign a user
*                          with a valid data to the DB
* Test inputs            : An id of a user with valid data
* Test expected output   : The function should return TRUE
* Test actual output     : As expected
*************************************************************************************/
static void TestCase52(void)
{
	unsigned char RET, Add_RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	Add_RET = DBM_Add_User(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(Add_RET, TRUE);
	RET = DBM_Delete_User(Test_User.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(RET, TRUE);
}

/************************************************************************************
* Test ID                : TestCase53
* Description            : Test the condition if(Enrollments[User_Id][course_id] == TRUE)
*                          of the function DBM_ShowCourse()
* Test Technique         : Decidion coverage
* Pre-requisits          : There is should be an empty place in the DB and assign a user
*                          with a valid data to the DB then add any 2 course (course_id = 1 
                           and course_id = 3) to this user
* Test inputs            : The id of the assigned user
* Test expected output   : The function print the data of the 2 courses (course_id = 1 and
*                          course_id = 3)
* Test actual output     : As expected
*************************************************************************************/
static void TestCase53(void)
{
	unsigned char Add_Delete_RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };
	
	Add_Delete_RET = DBM_Add_User(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(Add_Delete_RET, 1);


	DBM_AddToCourse(1, Test_User.PersonalInfo_Form.id);
	DBM_AddToCourse(3, Test_User.PersonalInfo_Form.id);

	DBM_ShowCourse(Test_User.PersonalInfo_Form.id);

	if (1 == Add_Delete_RET)
	{
		Add_Delete_RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(Add_Delete_RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase54
* Description            : Test the condition if(Enrollments[User_Id][course_id] == TRUE)
*                          of the function DBM_ShowCourse()
* Test Technique         : Decidion coverage
* Pre-requisits          : There is should be an empty place in the DB and assign a user
*                          with a valid data to the DB and don't add any course to this user
* Test inputs            : The id of the assigned user
* Test expected output   : The function shouldn't print any course data
* Test actual output     : As expected
*************************************************************************************/
static void TestCase54(void)
{
	unsigned char Add_Delete_RET;
	static struct User_Input_Type Test_User = { {-1, "Peter", 24, 18, 10, 2000, Male, Graduate}, {{"Peter.Nabil34", "PeterNabil123"}, "PeterNabil123"} };

	Add_Delete_RET = DBM_Add_User(&Test_User);
	Test_User.PersonalInfo_Form.id = current_user_test - 1;
	CU_ASSERT_EQUAL(Add_Delete_RET, 1);

	DBM_ShowCourse(Test_User.PersonalInfo_Form.id);

	if (1 == Add_Delete_RET)
	{
		Add_Delete_RET = Delete_Account(Test_User.PersonalInfo_Form.id);
		CU_ASSERT_EQUAL(Add_Delete_RET, TRUE);
	}
}

/************************************************************************************
* Test ID                : TestCase55
* Description            : Test DBM_DisplayAllCourses()
* Test Technique         : Experience-based Testing
* Pre-requisits          : No prerequisits
* Test inputs            : No inputs
* Test expected output   : It should print all the courses details
* Test actual output     : As expected
*************************************************************************************/
static void TestCase55(void)
{
	DBM_DisplayAllCourses();
}

void Main_Test_Runner(void)
{
	CU_initialize_registry();

	/*********************************** Default Tests *******************************************/
	/*
	CU_pSuite defaultSuite = CU_add_suite("Creaet Valid and InValid Account", NULL, NULL);
	CU_add_test(defaultSuite, "Creaet Valid Account", defaultTestCase1);
	CU_add_test(defaultSuite, "Creaet InValid Account", defaultTestCase2);
	*/
	/*********************************************************************************************/

	CU_pSuite ExploratorySuit = CU_add_suite("Exploratory Suit", NULL, NULL);
	CU_pSuite experienceBasedSuit = CU_add_suite("Experience-Based Suit", NULL, NULL);
	CU_pSuite Decision_Coverage_Suit = CU_add_suite("Decision Coverage Suit", NULL, NULL);
	CU_pSuite MC_DC_Suit = CU_add_suite("MC/DC Suit", NULL, NULL);
	CU_pSuite BVA_Suit = CU_add_suite("BVA Suit", NULL, NULL);
	
	CU_add_test(BVA_Suit, "Overload the DB", testCase1);
	CU_add_test(BVA_Suit, "Delete user with ID = MAX_USERS", testCase2);
	CU_add_test(experienceBasedSuit, "Name parameter is not letters", testCase3);
	CU_add_test(experienceBasedSuit, "Young person with educational_status = (PHD_Holder)", testCase4);
	CU_add_test(ExploratorySuit, "Testing user with educational_status = (PHD_Student)", testCase5);
	CU_add_test(BVA_Suit, "BVA_for_ShowStudentCourses()", TestCase7);
	CU_add_test(BVA_Suit, "BVA_for_ShowStudentCourses()", TestCase8);
	CU_add_test(BVA_Suit, "BVA_for_ShowStudentCourses()", TestCase9);
	CU_add_test(BVA_Suit, "BVA_for_ShowStudentCourses()", TestCase10);
	CU_add_test(BVA_Suit, "BVA_for_ShowStudentCourses()", TestCase11);
	CU_add_test(BVA_Suit, "BVA_for_ShowStudentCourses()", TestCase12);
	CU_add_test(BVA_Suit, "BVA_for_DBM_Delete_User()", TestCase13);
	CU_add_test(BVA_Suit, "BVA_for_DBM_Delete_User()", TestCase14);
	CU_add_test(BVA_Suit, "BVA_for_DBM_Delete_User()", TestCase15);
	CU_add_test(BVA_Suit, "BVA_for_DBM_Delete_User()", TestCase16);
	CU_add_test(BVA_Suit, "BVA_for_DBM_Delete_User()", TestCase17);
	CU_add_test(BVA_Suit, "BVA_for_DBM_Delete_User()", TestCase18);
	CU_add_test(BVA_Suit, "BVA__for_DBM_PrintUserData_Adminr()", TestCase19);
	CU_add_test(BVA_Suit, "BVA__for_DBM_PrintUserData_Adminr()", TestCase20);
	CU_add_test(BVA_Suit, "BVA__for_DBM_PrintUserData_Adminr()", TestCase21);
	CU_add_test(BVA_Suit, "BVA__for_DBM_PrintUserData_Adminr()", TestCase22);
	CU_add_test(BVA_Suit, "BVA__for_DBM_PrintUserData_Adminr()", TestCase23);
	CU_add_test(BVA_Suit, "BVA__for_DBM_PrintUserData_Adminr()", TestCase24);
	CU_add_test(BVA_Suit, "BVA_for_DBM_PrintUserData_User()", TestCase25);
	CU_add_test(BVA_Suit, "BVA_for_DBM_PrintUserData_User()", TestCase26);
	CU_add_test(BVA_Suit, "BVA_for_DBM_PrintUserData_User()", TestCase27);
	CU_add_test(BVA_Suit, "BVA_for_DBM_PrintUserData_User()", TestCase28);
	CU_add_test(BVA_Suit, "BVA_for_DBM_PrintUserData_User()", TestCase29);
	CU_add_test(BVA_Suit, "BVA_for_DBM_PrintUserData_User()", TestCase30);
	CU_add_test(BVA_Suit, "BVA_for_Delete_Account()", TestCase31);
	CU_add_test(BVA_Suit, "BVA_for_Delete_Account()", TestCase32);
	CU_add_test(BVA_Suit, "BVA_for_Delete_Account()", TestCase33);
	CU_add_test(BVA_Suit, "BVA_for_Delete_Account()", TestCase34);
	CU_add_test(BVA_Suit, "BVA_for_Delete_Account()", TestCase35);
	CU_add_test(BVA_Suit, "BVA_for_Delete_Account()", TestCase36);
	CU_add_test(BVA_Suit, "BVA_for_DBM_AddToCourse()", TestCase37);
	CU_add_test(BVA_Suit, "BVA_for_DBM_AddToCourse()", TestCase38);
	CU_add_test(MC_DC_Suit, "MC/DC_for_ShowStudentCourses()", TestCase39);
	CU_add_test(MC_DC_Suit, "MC/DC_for_ShowStudentCourses()", TestCase40);
	CU_add_test(MC_DC_Suit, "MC/DC_for_ShowStudentCourses()", TestCase41);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_AddStudentToCourse()", TestCase42);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_AddStudentToCourse()", TestCase43);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_AddStudentToCourse()", TestCase44);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_get_Gender_String()", TestCase45);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_get_Gender_String()", TestCase46);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_get_Gender_String()", TestCase47);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_DBM_Add_User()", TestCase48);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_DBM_Add_User()", TestCase49);
	CU_add_test(MC_DC_Suit, "MC/DC_for_DBM_Delete_User()", TestCase50);
	CU_add_test(MC_DC_Suit, "MC/DC_for_DBM_Delete_User()", TestCase51);
	CU_add_test(MC_DC_Suit, "MC/DC_for_DBM_Delete_User()", TestCase52);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_DBM_ShowCourse()", TestCase53);
	CU_add_test(Decision_Coverage_Suit, "Decidion_coverage_for_DBM_ShowCourse()", TestCase54);
	CU_add_test(experienceBasedSuit, "Test_DBM_DisplayAllCourses()", TestCase55);

	//CU_basic_set_mode(CU_BRM_VERBOSE);
	//CU_basic_run_tests();

	CU_console_run_tests();
	CU_cleanup_registry();
}
