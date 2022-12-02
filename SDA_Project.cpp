#include <iostream>
#include <list>
#include"mygraphics.h"
#include"myconsole.h"
#include <conio.h>
#include <ctime>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)// in order to use function in ctime library // SOLID PRINCIPES APPLIED

//-----------------------------------------------------------------
template<class T>
void increaseSize(T*& arr, int& size, int n)
{
    T* newarr = new T[size + n];
    for (int i = 0; i < size; i++)
        newarr[i] = arr[i];
    delete[] arr;
    arr = nullptr;
    arr = newarr;
    size += n;
}
//-----------------------------------------------------------------
template<class T>
void decreaseSize(T*& arr, int& size, int n)
{
    T* newarr = new T[size - n];
    for (int i = 0; i < size - n; i++)
        newarr[i] = arr[i];
    delete[] arr;
    arr = nullptr;
    arr = newarr;
    size -= n;
}
//-----------------------------------------------------------------

bool flag = 0;
 struct product_detail
 {
 	float price;
 	string item_name;
 	int quantity;
 	int id;
    product_detail()
    {
        price = 0;
        item_name = '\0';
        quantity = 0;
        id = 0;
    }
 	product_detail(int q, float p, string name)
 	{
 		price = p;
 		item_name = name;
 		quantity = q;
 	}

 } object;

 list<product_detail> qr; // global list to store inventory details

 class Employee;
 class cardFunction;
 class Buy_Product;
 class customer;
 class reset_card;
 class card;
 class store;
 class login_interface;
 class signup_interface;
 class View_Attendance;
 class Mark_Attendance;
 class View_Shift; 
 class Modify_Shift;
 class Count_of_Sales;
 class Store_Manager;
 class Store_Admin;
 class Best_Selling_Items;
 class Discount_Policies;
 class Update_on_Location;
 class inventory_manager;
 class online_customer;
 class walk_in_customer;
 class Attendance;
 class Shift_Management;
 class Scan_id;
 class Calculate_Bill;
 class Sales_Agent;
 class Floor_Manager;
 //------------------------------------------------------------------------

 class Employee
 {
 protected:
 	string name;
 	int id;
 	float salary;
 	string designation;
    int shift_hours;//changing

 public:
    //Best_Selling_Items* best_selling_items_ptr;
    //Discount_Policies* discount_policies_ptr;
 	Employee()
 	{
 		name = '\0';
 		id = 0;
 		salary = 0;
 		designation = '\0';
        shift_hours = 0;
        //best_selling_items_ptr = new Store_Manager;
        //discount_policies_ptr = new Store_Manager;
 	}
 	virtual string getname() = 0;
 	virtual int getid() = 0;
 	virtual float getsalary() = 0;
 	virtual string get_designation() = 0;
    virtual int get_shift_hours() = 0;
 	~Employee()
 	{
        
 	}
 };
 class Scan_id //interface implemented
 {
 public:
     virtual bool scan_rfid(int id) = 0;
 };
 class Calculate_Bill //interface implemented
 {
 public:
     virtual float calculate_bill(int quantity, float price, string item) = 0;
 };
 class Buy_Product //interface implemented
 {
 public:
     virtual void buy_product(list<struct  product_detail>) = 0;
 };
 
 

 
 class login_interface
 {
 public:
     virtual bool login() = 0;
 };
 class signup_interface
 {
 public:
     virtual bool signup() = 0;
 };


 class inventory_manager : public Employee
 { 
 public:
 	int quantity_of_products;

 	string getname()
 	{
 		return name;
 	}
 	int getid()
 	{
 		return id;
 	}
 	float getsalary()
 	{
 		return salary;
 	}
 	string get_designation()
 	{
 		return designation;
 	}

 	product_detail allocate(int quantity, float price, string item_name)
 	{
 		cout << "Enter name of the item to be added" << endl;
 		cin >> name;
 		object.item_name = name;

 		cout << "Enter quantity of the product to be allocated" << endl;
 		cin >> quantity;
 		object.quantity = quantity;

 		cout << "Enter price of the item " << endl;
 		cin >> price;
 		object.price = price;
 		cout << "Assigning ID to the product" << endl;

 		for (auto it = qr.begin(); it !=
 								   qr.end();
 			 ++it)
 		{
 			int x = rand() % 1000;

 			if (it->id != x)
 			{
 				object.id = x;
 				break;
 			}
 		}
 		qr.push_back(object); // store the product details in the List
 	}
 };

 //------------------------------------------------------------------------
 class View_Attendance //interface
 {
 public:
     virtual bool view_attendance() = 0;
 };
 class Mark_Attendance //interface
 {
 public:
     virtual bool mark_attendance() = 0;
 };
 class Attendance: public View_Attendance, public Mark_Attendance
 {
 public:
     bool status;
     bool mark_attendance() 
     {
         status = 1;
         return status;
     }
     bool view_attendance()
     {
         return status;
     }
 };
 class Count_of_Sales
 {
 public:
     virtual int view_sales() = 0;
 };

 class View_Shift
 {
 public:
     virtual int view_shift_hours() = 0;
 }; 
 
 class Modify_Shift
 {
 public:
     virtual int modified_shift_hours(int modified_shift_hours) = 0;
 };

 class Shift_Management : public View_Shift, public Modify_Shift
 {
 public:
     int shift_hours;
     int view_shift_hours()
     {
         return shift_hours;
     }
     int modified_shift_hours(int modified_shift_hours)
     {
         shift_hours = modified_shift_hours;
         return shift_hours;
     }
     Shift_Management()
     {
         shift_hours = 0;
     }
 };

 class Sales_Agent : public Employee, public Count_of_Sales
 {
 public:
     int count_of_sales;
     bool attendance_status;
     Mark_Attendance* mark_attendance_ptr;
     View_Shift* view_shift_hours_ptr; // sales  agent is accessing view_shift_hours function (which is present in shift management) througha interface view_shift

     string getname()
     {
         return name;
     }
     int getid()
     {
         return id;
     }
     float getsalary()
     {
         return salary;
     }
     string get_designation()
     {
         return designation;
     }
     int get_shift_hours()
     {
         return shift_hours;
     }
     int view_sales()
     {
         count_of_sales += 1;
         return count_of_sales;
     }
     Sales_Agent()
     {
         mark_attendance_ptr = new Attendance;
         view_shift_hours_ptr = new Shift_Management;
         count_of_sales = 0;
         attendance_status = 0;
     }
     ~Sales_Agent() 
     {
         if (mark_attendance_ptr != nullptr)
         {
             delete mark_attendance_ptr;
             mark_attendance_ptr = nullptr;
         }
         if (view_shift_hours_ptr != nullptr)
         {
             delete view_shift_hours_ptr;
             view_shift_hours_ptr = nullptr;
         }
     }
 };
 
 class Floor_Manager : public Employee
 {
 public:
     Count_of_Sales* view_report_ptr;
     View_Attendance* view_attendance_ptr;
     View_Shift* view_shift_hours_ptr;
     Modify_Shift* modify_shift_hours_ptr;
     string getname()
     {
         return name;
     }
     int getid()
     {
         return id;
     }
     float getsalary()
     {
         return salary;
     }
     string get_designation()
     {
         return designation;
     }
     int get_shift_hours()
     {
         return shift_hours;
     }
 };


 class Update_on_Location 
 {
 public:
     virtual void update_status_of_outlet(int i) = 0;//0 for create, 1 for update, 2 for delete
     virtual void move_employees(string location, string city) = 0;// check
 };

 class Store_Admin: public Employee, public Update_on_Location
 {
 public:
     bool reset_employees_acc() 
     {
         //dynamic employee will be destroyed here when he/she leaves the store.
     }
     string getname()
     {
         return name;
     }
     int getid()
     {
         return id;
     }
     float getsalary()
     {
         return salary;
     }
     string get_designation()
     {
         return designation;
     }
     int get_shift_hours()
     {
         return shift_hours;
     }
     void  update_status_of_outlet(int i) 
     {
         if (i==0)
         {
             cout << "Outlet Created." << endl;
         }
         else if(i==1)
         {
             cout << "Outlet Updated." << endl;
         }
         else
         {
             cout << "Outlet Deleted." << endl;
         }
     }
     void move_employees(string location, string city)
     {
         //check
     }
 };

//------------------------------------------------------------------------
 class cardFunction//interface
 {
 public:
     virtual string getcard_type() = 0;
     virtual bool getResetStatus() = 0;
     virtual int getloyalty_points() = 0;
     virtual string get_expiry_of_card() = 0;
 };

 class reset_card
 {
 public:
     virtual void reset(string date, int) = 0;
 };

 void get_date()//remaining
 {
     std::time_t t = std::time(0);   // get time now
     std::tm* now = std::localtime(&t);
     std::cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         << now->tm_mday
         << "\n";
 }

 class card: public reset_card,public cardFunction
 {
 protected:
     string	card_type;
     bool reset_status;
     int loyalty_points;
     string expiry_of_card; // 28/11/22
 public:
     card()
     {

     }
     void reset(string date, int)
     {
         loyalty_points = 0;
         //expiry_of_card
     }
     string getcard_type()
     {
         return card_type;
     }
     bool getResetStatus()
     {
         return reset_status;
     }
     int getloyalty_points()
     {
         return loyalty_points;
     }
     string get_expiry_of_card()
     {
         return expiry_of_card;
     }
     
 };

 class Best_Selling_Items
 {
 public:
     virtual string best_selling_item() = 0;// check it for attribute
 };
 class Discount_Policies
 {
 public:
     virtual float discount_policy(float d1, float d2) = 0;
 };

 class Store_Manager: public Employee, public Best_Selling_Items, public Discount_Policies
 {

 public:
     string getname()
     {
         return name;
     }
     int getid()
     {
         return id;
     }
     float getsalary()
     {
         return salary;
     }
     string get_designation()
     {
         return designation;
     }
     int get_shift_hours()
     {
         return shift_hours;
     }
     string best_selling_item() 
     {
         // check
         cout << "Hello World" << endl;
         string str = "\0";
         return str;
     }
     float discount_policy(float d1, float d2) 
     {
         if (d1 > d2) 
         {
             return d1;
         }
         return d2;
     }
 };
 
 class store : public Buy_Product, public Scan_id, public Calculate_Bill
 {
 public:
     Best_Selling_Items* best_selling_items_ptr;
     Discount_Policies* discount_policies_ptr;
     Update_on_Location* Update_on_Location_ptr;
     cardFunction* card_Function_ptr;
     reset_card* reset_card_ptr;
     string location;
     string city;
     float local_product_discount;
     float price;
     int count_of_sales;
     string status;

     store()
     {
         reset_card_ptr = new card();
         best_selling_items_ptr = new Store_Manager;
         discount_policies_ptr = new Store_Manager;
         Update_on_Location_ptr = new Store_Admin;
         card_Function_ptr = new card[10];
         location = "\0";
         city = "\0";
         local_product_discount = 0;
         price = 0;
         count_of_sales = 0;
         status = "\0";
     }
     bool scan_rfid(int id)
     {
         //id = custom->rfid;
         if (id == 0)
         {
             return 0;
         }
         return 1;
     }
     float calculate_bill(int quantity, float price, string item)
     {
         float total_bill = 0;

         cout << "ITEM NAME:" << item << endl;
         cout << "ITEM PRICE:" << price << endl;
         cout << "ITEM QUANTITY:" << quantity << endl;

         total_bill = price * quantity;
         cout << "YOUR TOTAL BILL IS" << total_bill << endl;

         cout << "THANK YOUR FOR SHOPPING at S&J BOUTIQUES" << endl;
     }
     void buy_product(list<product_detail>)
     {

     }
     ~store()
     {
         if (best_selling_items_ptr != nullptr)
         {
             delete best_selling_items_ptr;
             best_selling_items_ptr = nullptr;
         }
         if (discount_policies_ptr != nullptr)
         {
             delete discount_policies_ptr;
             discount_policies_ptr = nullptr;
         }
         if (Update_on_Location_ptr != nullptr)
         {
             delete Update_on_Location_ptr;
             Update_on_Location_ptr = nullptr;
         }
         if (card_Function_ptr != nullptr)
         {
             delete[]card_Function_ptr;
             card_Function_ptr = nullptr;
         }
         if (reset_card_ptr != nullptr)
         {
             delete[]reset_card_ptr;
             reset_card_ptr = nullptr;
         }
     }
 };

 class customer
 {
 public:
     Buy_Product* buy_product_ptr;
     cardFunction* cardFunction_ptr;
     string name;
     char gender;
     bool picture;
     string category;
     string type;

     customer()
     {
         buy_product_ptr = new store;
         cardFunction_ptr = new card;
         name = "\0";
         gender = '\0';
         picture = false;
         category = "\0";
         type = "\0";
     }
     virtual  string getname() = 0;
     virtual  char getgender() = 0;
     virtual  bool getpicture() = 0;
     virtual  string getcategory() = 0;
     virtual  string gettype() = 0;

     ~customer()
     {
         if (buy_product_ptr != nullptr)
         {
             delete buy_product_ptr;
             buy_product_ptr = nullptr;
         }
         if (cardFunction_ptr != nullptr)
         {
             delete cardFunction_ptr;
             cardFunction_ptr = nullptr;
         }
     }
 };

 class walk_in_customer : public customer
 {
     string getname()
     {
         return name;
     }
     char getgender()
     {
         return gender;
     }
     bool getpicture()
     {
         return picture;
     }
     string getcategory()
     {
         return category;
     }
     string gettype()
     {
         return type;
     }
 };

 class online_customer : public customer, public login_interface, public signup_interface
 {
 public:
     string password;
     string email;

     online_customer()
     {
         password = "\0";
         email = "\0";
     }
     string getname()
     {
         return name;
     }
     char getgender()
     {
         return gender;
     }
     bool getpicture()
     {
         return picture;
     }
     string getcategory()
     {
         return category;
     }
     string gettype() // will be null
     {
         return type;
     }
     bool login()
     {

         cout << "WELCOME USER" << endl;
         cout << "--------------LOGIN----------------" << endl;
         cout << "ENTER YOUR CREDENTIALS TO LOGIN" << endl;
         cout << "Enter your email" << endl;
         cin >> email;
         cout << "Enter your password" << endl;
         cin >> password;
         return 1;
     }
     bool signup(string username)
     {
         cout << "WELCOME USER" << endl;
         cout << "--------------SIGNUP----------------" << endl;
         cout << "ENTER YOUR CREDENTIALS TO SIGNUP" << endl;
         cout << "Enter your username" << endl;
         cin >> username;
         name = username;
         cout << "Enter your password" << endl;
         cin >> password;
         cout << "Enter your Email" << endl;
         cin >> email;
         return 1;
     }
 };
 //--------------------------------------------------------------------

COLORREF black = RGB(0, 0, 0);
COLORREF white = RGB(255, 255, 255);
COLORREF red = RGB(255, 0, 0);
COLORREF skyblue = RGB(135, 206, 235);
COLORREF pink = RGB(236, 188, 180);
COLORREF gray = RGB(50, 50, 50);
COLORREF green = RGB(34, 139, 34);
COLORREF blue = RGB(0, 0, 128);
COLORREF yellow = RGB(255, 255, 0);
COLORREF cyan = RGB(0, 255, 255);

void boundry()
{
	myLine(8, 8, 8, 480, blue);//left y
	myLine(955, 8, 955, 480, red);//right y

	myLine(10, 8, 955, 8, green);//up 
	myLine(8, 480, 955, 480, yellow);//down
}

void clearscreen()
{
	myRect(0, 0, 1400, 900, black, black);
}

void _menu()
{
	boundry();
	char str2[] = { "PRESS A FOR BOUTIQUE MANAGEMENT" };
	myDrawTextWithFont(350, 150, 40, str2, black, white);
	char str3[] = { "PRESS B FOR CUSTOMER" };
	myDrawTextWithFont(350, 200, 40, str3, black, white);
	char str4[] = { "PRESS C FOR EXIT" };
	myDrawTextWithFont(350, 250, 40, str4, black, white);
}

void welcome()
{
	boundry();
	COLORREF black = RGB(0, 0, 0);
	COLORREF white = RGB(255, 255, 255);
	char str[] = { " WELCOME " };
	char str2[] = { " S.J BOUTIQUE " };
	char str3[] = {" Press any key to continue.... "};
	myDrawTextWithFont(350, 170, 80, str, black, white);
	myDrawTextWithFont(310, 20, 80, str2, blue, white);
	myDrawText(370, 450, 30, str3, white, NULL);
	_getch();
}

int main()
{
    
    Sales_Agent agent_obj;
    agent_obj.attendance_status = 0;
    cout << agent_obj.attendance_status << endl;

    cout<<agent_obj.view_shift_hours_ptr->view_shift_hours();

    agent_obj.best_selling_items_ptr->best_selling_item();

    
    agent_obj.attendance_status= agent_obj.mark_attendance_ptr->mark_attendance();
    //cout<<"ATTENDENCE = " << obj.attendance_status << endl;

    Floor_Manager floor_obj;
    floor_obj.modify_shift_hours_ptr->modified_shift_hours(4);
    floor_obj.view_shift_hours_ptr->view_shift_hours();
    floor_obj.view_attendance_ptr->view_attendance();
    floor_obj.view_report_ptr->view_sales();

    card card_obj; //check

    store store_obj; //check
    store_obj.Update_on_Location_ptr->move_employees("Johar Town","Lahore");
    store_obj.Update_on_Location_ptr->update_status_of_outlet();
    
    Store_Manager store_manager_obj; //check
    store_manager_obj.best_selling_item();
    store_manager_obj.discount_policy(50,60);



	//bool flag1 = 0;
	//char menu;
	//welcome();
	//while (flag1 == 0)
	//{
	//	flag = 0;
	//	while (flag == 0)
	//	{
	//		clearscreen();
	//		_menu();
	//		menu = _getch();

	//		if (menu == 97 || menu == 65)// for store MANAGEMENT
	//		{	
 //               
	//			clearscreen();
	//			boundry();

 //               char str2[] = { "PRESS 1 TO STORE ADMIN" };
 //               myDrawTextWithFont(350, 150, 40, str2, black, red);
 //               char str3[] = { "PRESS 2 TO STORE MANAGER" };
 //               myDrawTextWithFont(350, 200, 40, str3, black, red);
 //               char str4[] = { "PRESS 3 TO INVENTORY MANAGER" };
 //               myDrawTextWithFont(350, 250, 40, str4, black, red);
 //               char str5[] = { "PRESS 4 TO FLOOR MANAGER" };
 //               myDrawTextWithFont(350, 300, 40, str5, black, red);
 //               char str6[] = { "PRESS 5 TO SALES AGENT" };
 //               myDrawTextWithFont(350, 350, 40, str6, black, red);

 //               char temp = _getch();
 //               if(temp== 49) //show admin funcnalities
 //               {
 //                   clearscreen();
 //                   boundry();
 //                   char str2[] = { "PRESS 1 TO RESET EMPLOYEE ACCOUNT" };
 //                   myDrawTextWithFont(350, 150, 40, str2, black, cyan);
 //                   char str3[] = { "PRESS 2 TO UPDATE OF OUTLET" };
 //                   myDrawTextWithFont(350, 200, 40, str3, black, cyan);
 //                   char str4[] = { "PRESS 3 TO TRANSFER EMPLOYEE" };
 //                   myDrawTextWithFont(350, 250, 40, str4, black, cyan);
 //               }
 //               else if(temp == 50)//show manager funcnalities
 //               {
 //                   clearscreen();
 //                   boundry();
 //                   char str2[] = { "PRESS 1 TO DETERMINE BEST SELLING ITEM" };
 //                   myDrawTextWithFont(350, 150, 40, str2, black, gray);
 //                   char str3[] = { "PRESS 2 TO MAKE DISCOUNT POLICY " };
 //                   myDrawTextWithFont(350, 200, 40, str3, black, gray);
 //               }
 //               else if (temp == 51)//show inventory manager funcnalities
 //               {
 //                   clearscreen();
 //                   boundry();
 //                   char str2[] = { "PRESS 1 TO ALLOCATE INVENTORY" };
 //                   myDrawTextWithFont(350, 150, 40, str2, black, pink);
 //                   char str3[] = { "PRESS 2 TO MAKE STOCK RESERVATION POLICY " };
 //                   myDrawTextWithFont(350, 200, 40, str3, black, pink);
 //               }
 //               else if (temp == 52)//show floor funcnalities
 //               {
 //                   clearscreen();
 //                   boundry();
 //                   char str2[] = { "PRESS 1 TO MANAGE SALES AGENT PERFORMANCE" };
 //                   myDrawTextWithFont(350, 150, 40, str2, black, skyblue);
 //                   char str3[] = { "PRESS 2 TO MANAGE RETURN OF ITEMS" };
 //                   myDrawTextWithFont(350, 200, 40, str3, black, skyblue);
 //                   char str4[] = { "PRESS 3 TO VIEW SHIFT HOURS" };
 //                   myDrawTextWithFont(350, 250, 40, str4, black, skyblue);
 //               }
 //               else if (temp == 53)//show sales agent funcnalities
 //               {
 //                   clearscreen();
 //                   boundry();
 //                   char str2[] = { "PRESS 1 TO VIEW SALES" };
 //                   myDrawTextWithFont(350, 150, 40, str2, black, green);
 //                   char str3[] = { "PRESS 2 TO MARK ATTENDANCE" };
 //                   myDrawTextWithFont(350, 200, 40, str3, black, green);
 //               }

	//			_getch();
	//		}
	//		else if (menu == 98 || menu == 66)// for customer
	//		{
	//			clearscreen();
	//			boundry();

 //               char str6[] = { "PRESS 1 FOR ONLINE CUSTOMER" };
 //               myDrawTextWithFont(340, 150, 40, str6, black, red);
 //               char str7[] = { "PRESS 2 FOR WALK IN CUSTOMER" };
 //               myDrawTextWithFont(340, 200, 40, str7, black, red);

 //               char str=_getch();

 //               if (str==49)// ONLINE CUSTOMER
 //               {
 //                   clearscreen();
 //                   boundry();
 //                   char str6[] = { "PRESS 1 FOR NEW CUSTOMER" };
 //                   myDrawTextWithFont(340, 150, 40, str6, black, cyan);
 //                   char str7[] = { "PRESS 2 FOR OLD CUSTOMER" };
 //                   myDrawTextWithFont(340, 200, 40, str7, black, cyan);
 //                   str = _getch();
 //                   clearscreen();
 //                   boundry();
 //                   if(str==49)
 //                   {
 //                       char str6[] = { "PRESS 1 FOR LOGIN" };
 //                       myDrawTextWithFont(340, 150, 40, str6, black, gray);
 //                   }
 //                   else if(str==50)
 //                   {
 //                       char str6[] = { "PRESS 2 FOR SIGNUP" };
 //                       myDrawTextWithFont(340, 150, 40, str6, black, gray);
 //                   }
 //               }
 //               else if (str == 50)//WALK IN
 //               {
 //                   clearscreen();
 //                   boundry();
 //                   char str6[] = { "PRESS 1 TO BUY PRODUCTS" };
 //                   myDrawTextWithFont(340, 150, 40, str6, black, gray);
 //                   char str = _getch();
 //                   if (str==49)
 //                   {
 //                      //show products
 //                   }
 //               }

	//			
	//		}
	//		else if (menu == 99 || menu == 67)// for exit
	//		{
	//			clearscreen();
	//			boundry();
	//			char str6[] = { "!THANK YOU!" };
	//			myDrawTextWithFont(340, 200, 80, str6, black, white);
	//			flag = 1;
	//			flag1 = 1;
	//		}
	//	}
	//}
	//_getch();
	//system("pause");

	return 0;
}