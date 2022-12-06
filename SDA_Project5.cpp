#include <iostream>
#include <list>
#include"mygraphics.h"
#include"myconsole.h"
#include <conio.h>
#include <ctime>
#include<fstream>
#include<iterator>
#include <windows.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)// in order to use function in ctime library 

// SOLID PRINCIPES APPLIED

bool flag = 0;
int fix = 0;
struct customer_info {

public:
    string name;
    string gender;
    bool picture;
    string category;
    string type;
    string password;
    string email;
    customer_info() 
    {
        name = "\0";
        gender = '\0';
        picture = 0;
        category = "\0";
        type = "\0";
        password = "\0";
        email = "\0";
    }
};

customer_info* customer_details = new customer_info[1]; // array to store data for walk in customer
customer_info* online_details= new customer_info[1]; // array to store data for online customer
 
int customer_details_size = 1; // size for walk in customer
int online_size = 1; // size for online customer

struct product_detail
{
public:
    float price;
    string item_name;
    int quantity;
    int id;
    product_detail()
    {
        price = 0;
        item_name = "\0";
        quantity = 0;
        id = 0;
    }
    product_detail(int i, int q, float p, string name)
    {
        price = p;
        item_name = name;
        quantity = q;
        id = i;
    }
} object;
float total_bill = 0;

product_detail* product_array = new product_detail[1]; // To cater the multiple shoping of customer.

list<product_detail> qr; // global list to store inventory i.e unique products are present at every index. This will be populated through allocate inventory.
int _id = 0;
int customer_count = 0;

bool check_avail(int _id, int no_of_item) {

    for (auto it = qr.begin(); it != qr.end(); ++it)//it is struct
    {
        if (it->id == _id) // we have reached specific id we want to buy
        {
            if (it->quantity >= no_of_item) {
                return 1;
            }
        }
    }
    return 0;
}
void Update_Inventory(int _id, int no_of_items)
{
    for (auto it = qr.begin(); it != qr.end(); ++it)//it is struct
    {
        if (it->id == _id) // we have reached specific id we want to buy
        {
            if (it->quantity>=no_of_items) {

                it->quantity -= no_of_items;
            }
            else if (it->quantity<no_of_items && it->quantity!=0) {

                cout << it->item_name << "  Quantity left = " << it->quantity<<". Sorry for inconvenience ." << endl;
            }
            else {
                cout << it->item_name << " is Out of Stock. Sorry for inconvenience ." << endl;
            }           
        }
    }
    //customer buying array.
}
template<class T>
void increaseSize(T*& arr, int& size)
{
    T* newarr = new T[size + 1];
    for (int i = 0; i < size; i++)
        newarr[i] = arr[i];
    delete[] arr;
    arr = nullptr;
    arr = newarr;
    size++;
}

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
    virtual float calculate_bill(int quantity, float price) = 0;
};
class Buy_Product //interface implemented
{
public:
    virtual void buy_product() = 0;
};

class login_interface
{
public:
    virtual void login() = 0;
};
class signup_interface
{
public:
    virtual void signup() = 0;
};

class inventory_manager : public Employee
{
public:
    int quantity_of_products;
    int get_shift_hours()
    {
        return shift_hours;
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
    inventory_manager()
    {
        quantity_of_products = 0;
    }
    void allocate(int quantity, float price, string item_name)
    {
        bool temp3 = 1;
        for (auto it = qr.begin(); it != qr.end(); ++it)
        {
            if (it->item_name == item_name)
            {
                it->quantity += quantity;
                temp3 = 0;
                break;
            }
            temp3 = 1;
        }

        if (temp3 == 1)
        {
            //cout << "Enter name of the item to be added" << endl;
            //cin >> name;
            object.item_name = item_name;

            //cout << "Enter quantity of the product to be allocated" << endl;
            //cin >> quantity;
            object.quantity = quantity;

            //cout << "Enter price of the item " << endl;
            //cin >> price;
            object.price = price;
            //cout << "Assigning ID to the product" << endl;

           /* for (auto it = qr.begin(); it != qr.end(); ++it)
            {
                int x = rand() % 1000;
                if (it->id != x)
                {
                    object.id = x;
                    break;
                }
            }*/

            _id += 1;
            object.id = _id;

            qr.push_back(object); // store the product details in the List
        }
    }
};

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
class Attendance : public View_Attendance, public Mark_Attendance
{
public:
    bool status;
    Attendance()
    {
        status = 0;
    }
    bool mark_attendance()
    {
        status = 1;
        return status;
    }
    bool view_attendance()
    {
        return status;
    }
    ~Attendance() {}
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
    View_Shift* view_shift_hours_ptr; // sales  agent is accessing view_shift_hours function (which is present in shift management) through a interface view_shift

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
    //~Sales_Agent() 
    //{
    //    if (mark_attendance_ptr != nullptr)
    //    {
    //        delete mark_attendance_ptr;
    //        mark_attendance_ptr = nullptr;
    //    }
    //    if (view_shift_hours_ptr != nullptr)
    //    {
    //        delete view_shift_hours_ptr;
    //        view_shift_hours_ptr = nullptr;
    //    }
    //}
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
    Floor_Manager()
    {
        view_report_ptr = new Sales_Agent;// To View Sales
        view_attendance_ptr = new Attendance[10];
        view_shift_hours_ptr = new Shift_Management[10];
        modify_shift_hours_ptr = new Shift_Management[10];
    }
    ~Floor_Manager()
    {
        if (view_report_ptr != nullptr)
        {
            delete view_report_ptr;
            view_report_ptr = nullptr;
        }
        if (view_attendance_ptr != nullptr)
        {
            delete[] view_attendance_ptr;
            view_attendance_ptr = nullptr;
        }
        if (view_shift_hours_ptr != nullptr)
        {
            delete[] view_shift_hours_ptr;
            view_shift_hours_ptr = nullptr;
        }
        if (modify_shift_hours_ptr != nullptr)
        {
            delete[] modify_shift_hours_ptr;
            modify_shift_hours_ptr = nullptr;
        }
    }
};

class Update_on_Location
{
public:
    virtual void update_status_of_outlet(int i) = 0;//0 for create, 1 for update, 2 for delete
    virtual void move_employees(string location, string city) = 0;// check
};

class Store_Admin : public Employee, public Update_on_Location
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
        if (i == 0)
        {
            cout << "Outlet Created." << endl;
        }
        else if (i == 1)
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
    ~Store_Admin()
    {

    }
};

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

class card : public reset_card, public cardFunction
{
protected:
    string	card_type;
    bool reset_status;
    int loyalty_points;
    string expiry_of_card; // 28/11/22
public:
    card()
    {
        card_type = '\0';
        reset_status = 0;
        loyalty_points = 0;
        expiry_of_card = '\0';
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
    ~card()
    {
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

class Store_Manager : public Employee, public Best_Selling_Items, public Discount_Policies
{
public:
    Store_Manager() {
        
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
    string best_selling_item()
    {
        string top_item = "\0";
        int max = 1000;
        for (auto it = qr.begin(); it != qr.end(); ++it)
        {
            if (it->quantity < max) {
                max = it->quantity;
                top_item = it->item_name;
            }

        }
        return top_item;
    }
    float discount_policy(float d1, float d2)
    {
        if (d1 > d2)
        {
            return d1;
        }
        return d2;
    }
    void record_customer_details()
    {
       
        string name;
        char gender;
        bool picture;
        string category;
        string type;

        ifstream fin;
        fin.open("customer.txt");

        if (fin.is_open()) {
            while (!fin.eof()) 
            {
                bool temp3 = 1;
                fin >> name;

                //cout << name << endl;
                for (int i = 0; i < customer_details_size; i++)
                {
                    if (customer_details[i].name == name)
                    {  
                        fin >> name;
                        fin >> name;
                        fin >> name;
                        fin >> name;
                        temp3 = 0;

                        break;
                    }
                    temp3 = 1;
                }

                if (temp3 == 1)
                {

                    customer_details[customer_details_size - 1].name = name;
                    fin >> gender;
                    // cout << gender << endl;

                    customer_details[customer_details_size - 1].gender = gender;
                    fin >> picture;
                    //cout << picture << endl;

                    customer_details[customer_details_size - 1].picture = picture;
                    fin >> category;
                    // cout << category << endl;

                    customer_details[customer_details_size - 1].category = category;
                    fin >> type;
                    // cout << type << endl;

                    customer_details[customer_details_size - 1].type = type;

                    //cout << "value of customer_details_size is" << customer_details_size << endl;
                    increaseSize(customer_details, customer_details_size);
                    //  cout << "value of customer_details_size is" << customer_details_size << endl;
                }
            }
        }
        fin.close();
    }
    void view_customer_details() {

        //cout << "value of customer_details_size in view function " << customer_details_size << endl;

        for (int i = 0; i < (customer_details_size-1); i++) {
            cout << "NAME OF THE CUSTOMER:" << customer_details[i].name << endl;
            cout << "GENDER OF THE CUSTOMER:" << customer_details[i].gender << endl;
            cout << "PICTURE AVAILABLITIY THE CUSTOMER:" << customer_details[i].picture << endl;
            cout << "CATEGORY OF THE CUSTOMER:" << customer_details[i].category << endl;
            cout << "TYPE OF THE CUSTOMER:" << customer_details[i].type << endl;
            cout << "------------------------------------------------------------------" << endl << endl;

        }
    }
    ~Store_Manager()
    {
    }
};

class store : public Scan_id, public Calculate_Bill
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
    float calculate_bill(int quantity, float price) //card and discount policy implementation
    {
        float total_bill = 0;
        total_bill = price * quantity;
        return total_bill;
    }
    void view_product()
    {
        for (auto it = qr.begin(); it != qr.end(); ++it)
        {
            cout << "Product Details for item :" << it->id << endl;
            cout << "Item name                :" << it->item_name << endl;
            cout << "Item Quantity            :" << it->quantity << endl;
            cout << "Item Price               :" << it->price << endl;
        }
    }
    void view_customer_details()
    {
        //
    }
    ~store()
    {
        /*
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
        }*/
    }
};

class customer :public Buy_Product
{
public:
    cardFunction* cardFunction_ptr;
    Calculate_Bill* calculate_bill_ptr;
    string name;
    char gender;
    bool picture;
    string category;
    string type;

    customer()
    {
        calculate_bill_ptr = new store;
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
    virtual  void buy_product() = 0;

   /* ~customer()
    {
        if (cardFunction_ptr != nullptr)
        {
            delete cardFunction_ptr;
            cardFunction_ptr = nullptr;
        }
    }*/
};

string find_name(int _id)
{
    string str = "Item_Name Not Found!";
    for (auto it = qr.begin(); it != qr.end(); ++it)
    {
        if (it->id == _id)
        {
            return it->item_name;
        }
    }
    return str;
}
float find_price(int _id)
{
    for (auto it = qr.begin(); it != qr.end(); ++it)
    {
        if (it->id == _id)
        {
            return it->price;
        }
    }
    return -1;
}

class walk_in_customer : public customer
{
public:
    walk_in_customer()
    {
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
    string gettype()
    {
        return type;
    }
    void buy_product()
    {
        int temp = 0;
        int no_of_items = 0;
        char ch = '\0';
        int size = 1;
        float total_bill = 0;
        bool flag = true;
        cout << "WELCOME " << customer_details[fix].name << endl << endl;
        while (true)
        {
            cout << "(1) PRESS B TO BUY :" << endl << endl;
            cout << "(2) PRESS E TO EXIT:" << endl;
            ch = _getch();
            no_of_items = 0;

            if (ch == 'e' || ch == 'E')
            {
                if (total_bill == 0)
                {
                    cout << "You have not purchased any product :(" << endl;
                    break;
                }

                break;
            }
            else if (ch == 'b' || ch == 'B')
            {

                for (auto it = qr.begin(); it != qr.end(); ++it)
                {
                    cout << "Product Details for item :" << it->id << endl;
                    cout << "Item name                :" << it->item_name << endl;
                    cout << "Item Quantity            :" << it->quantity << endl;
                    cout << "Item Price               :" << it->price << endl;
                    cout << endl;
                }
                cout << endl;
                cout << "Please select id to buy your product:" << endl;
                cin >> temp;
                if (temp == 1)
                {
                    cout << "Enter the quantity:" << endl;
                    cin >> no_of_items;
                    if (check_avail(temp, no_of_items) == 1) {
                        product_array[size - 1].price = find_price(temp);
                        product_array[size - 1].item_name = find_name(temp);
                        product_array[size - 1].quantity = no_of_items;
                        product_array[size - 1].id = temp;
                        Update_Inventory(temp, no_of_items);
                        total_bill += calculate_bill_ptr->calculate_bill(product_array[size - 1].quantity, product_array[size - 1].price);
                        increaseSize(product_array, size);
                        cout << "PRODUCT SUCCESSFULLY PURCHASED!" << endl << endl;
                    }
                    else {
                        cout << "The selected product is out of stock. Sorry for inconveience." << endl << endl;
                    }
                }
                else if (temp == 2)
                {
                    cout << "Enter the quantity:" << endl;
                    cin >> no_of_items;
                    if (check_avail(temp, no_of_items) == 1) {
                        product_array[size - 1].price = find_price(temp);
                        product_array[size - 1].item_name = find_name(temp);
                        product_array[size - 1].quantity = no_of_items;
                        product_array[size - 1].id = temp;
                        Update_Inventory(temp, no_of_items);//updating inventory
                        total_bill += calculate_bill_ptr->calculate_bill(product_array[size - 1].quantity, product_array[size - 1].price);
                        increaseSize(product_array, size);
                        cout << "PRODUCT SUCCESSFULLY PURCHASED!" << endl << endl;
                    }
                    else {
                        cout << "The selected product is out of stock.Sorry of inconveience" << endl;
                    }
                }
                else if (temp == 3)
                {
                    cout << "Enter the quantity:" << endl;
                    cin >> no_of_items;
                    if (check_avail(temp, no_of_items) == 1) {
                        product_array[size - 1].price = find_price(temp);
                        product_array[size - 1].item_name = find_name(temp);
                        product_array[size - 1].quantity = no_of_items;
                        product_array[size - 1].id = temp;
                        Update_Inventory(temp, no_of_items);
                        total_bill += calculate_bill_ptr->calculate_bill(product_array[size - 1].quantity, product_array[size - 1].price);
                        increaseSize(product_array, size);
                        cout << "PRODUCT SUCCESSFULLY PURCHASED!" << endl << endl;
                    }
                    else {
                        cout << "The selected product is out of stock.Sorry of inconveience" << endl;
                    }
                }
            }
        }
        if (total_bill != 0)
        {
            float temp1 = total_bill;
            total_bill = total_bill * 1.17;
            float gst = total_bill - temp1;

            cout << endl << endl;
            cout << "*********" << endl;
            cout << "*RECIEPT*" << endl;
            cout << "*********" << endl;
            for (int i = 0; i < (size - 1); i++)
            {
                //cout << "product details for item :" << product_array[i].id << endl;
                cout << "Item Name : " << product_array[i].item_name << "   Item Quantity :" << product_array[i].quantity << endl;
                //cout << "item price               :" << product_array[i].price<< endl;
            }
            cout << "Calculated Bill    = " << temp1 << endl;
            cout << "17 % GST APPLIED   = " << gst << endl;
            cout << "YOUR TOTAL BILL IS = " << total_bill << endl;
            cout << "THANK YOUR FOR SHOPPING at S&J BOUTIQUES" << endl;
            cout << endl;
            cout << "******************************************" << endl;
            /*  cout << "Updated Inventory" << endl;
              for (auto it = qr.begin(); it != qr.end(); ++it)
              {
                  cout << "product details for item :" << it->id << endl;
                  cout << "item name                :" << it->item_name << endl;
                  cout << "item quantity            :" << it->quantity << endl;
                  cout << "item price               :" << it->price << endl;
              }*/
        }
    }
    ~walk_in_customer()
    {

    }
};

class online_customer : public customer, public login_interface, public signup_interface
{
public:
    online_customer()
    {
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
    
    void record_online_customer_details()
    {
        string name;
        string gender;
        bool picture;
        string category;
        string type;
        string email;
        string password;

        ifstream fin;
        fin.open("online.txt");

        if (fin.is_open()) {
            while (!fin.eof()) 
            {
                bool temp3 = 1;
                fin >> name;

                //cout << name << endl;
                for (int i = 0; i < online_size; i++)
                {
                    if (online_details[i].name == name)
                    {
                        fin >> name;
                        fin >> name;
                        fin >> name;
                        fin >> name;
                        fin >> name;
                        fin >> name;
                        temp3 = 0;

                        break;
                    }
                    temp3 = 1;
                }

                if (temp3 == 1)
                {

                    online_details[online_size - 1].name = name;
                    fin >> gender;
                    // cout << gender << endl;

                    online_details[online_size - 1].gender = gender;
                    fin >> picture;
                    //cout << picture << endl;

                    online_details[online_size - 1].picture = picture;
                    fin >> category;
                    // cout << category << endl;

                    online_details[online_size - 1].category = category;
                    fin >> type;
                    // cout << type << endl;

                    online_details[online_size - 1].type = type;

                    fin >> email;
                    // cout << type << endl;

                    online_details[online_size - 1].email = email;

                    fin >> password;

                    online_details[online_size - 1].password = password;

                    //cout << "value of customer_details_size is" << customer_details_size << endl;
                    increaseSize(online_details, online_size);
                    //  cout << "value of customer_details_size is" << customer_details_size << endl;
                }
            }
        }
        fin.close();
     
    }
    void view_online_customer_details() {

        //cout << "value of customer_details_size in view function " << customer_details_size << endl;

        for (int i = 0; i < (online_size - 1); i++) {

            cout << "NAME OF THE CUSTOMER:" << online_details[i].name << endl;
            cout << "GENDER OF THE CUSTOMER:" << online_details[i].gender << endl;
            cout << "PICTURE AVAILABLITIY THE CUSTOMER:" << online_details[i].picture << endl;
            cout << "CATEGORY OF THE CUSTOMER:" << online_details[i].category << endl;
            cout << "TYPE OF THE CUSTOMER:" << online_details[i].type << endl;
            cout << "Email of Customer:" << online_details[i].email << endl;
            cout << "Password of Customer:" << online_details[i].password << endl;

            cout << "------------------------------------------------------------------" << endl << endl;
        }
    }
    void login()
    {
        string password;
        string email;

        cout << "WELCOME USER" << endl;
        cout << "--------------LOGIN----------------" << endl;
        cout << "ENTER YOUR CREDENTIALS TO LOGIN" << endl;
        cout << "Enter your email" << endl;
        cin >> email;
        cout << "Enter your password" << endl;
        cin >> password;
        bool flag = 0;

        for (int i = 0; i < online_size-1; i++) {

            if (online_details[i].email == email && online_details[i].password == password) {
                cout << "Welcome Back " << online_details[i].name << "  You have been successfully Logged in" << endl << endl;
                flag = 0;
                break;

            }
            else if (online_details[i].email == email && online_details[i].password != password) {

                cout << " Your Password is incorrect.Please try again" << endl << endl;
                flag = 0;
                break;

            }
            else {
                flag = 1;
            }
        }
        if (flag==1) {
            cout << "No Such previous account exist" << endl;
        }
           
       
    }
    void  signup()
    {
        string name;
        char gender;
        bool picture;
        string category;
        string type;
        string password;
        string email;

        cout << "WELCOME USER" << endl;
        cout << "--------------SIGNUP----------------" << endl;
        cout << "ENTER YOUR CREDENTIALS TO SIGNUP" << endl;
        cout << "Enter your username" << endl;
        cin >> name;
    
        online_details[online_size].name = name;
        cout << online_details[online_size].name;

        cout << "Enter your gender" << endl;
        cin >> gender;
        
        online_details[online_size].gender = gender;
        cout << online_details[online_size].gender << endl;

        cout << "Do you have a profile picture. Enter 1 for YES and 0 for NO" << endl;
        cin >> picture;
       
        online_details[online_size].picture = picture;

        cout << online_details[online_size].picture << endl;

        online_details[online_size].type = type;

        cout << online_details[online_size].type << endl;

        cout << "Enter your Email" << endl;
        cin >> email;
        
        online_details[online_size].email = email;

        cout << online_details[online_size].email << endl;

        cout << "Enter your password" << endl;
        cin >> password;
        
        online_details[online_size].password = password;

        cout << online_details[online_size].password << endl;

       
        ofstream fout;
        fout.open("online.txt",ios::app);
        cout << "Inside writing function for file" << endl;
        if (fout.is_open()) {
            fout << name;
            fout << '\n';
            fout << gender;
            fout << '\n';
            fout << picture;
            fout << '\n';
            fout << email;
            fout << '\n';
            fout << password;
            fout << '\n';

        }
        fout.close();
    }
    void buy_product()
    {

        //else//app 4% gst if on card;
        //{
        //    total_bill = total_bill * 1.04;
        //}


    }
    ~online_customer() {

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
    char str3[] = { " Press any key to continue.... " };
    myDrawTextWithFont(350, 170, 80, str, black, white);
    myDrawTextWithFont(310, 20, 80, str2, blue, white);
    myDrawText(370, 450, 30, str3, white, NULL);
    _getch();
}

void clear() {
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

int main()
{
    store store_obj;
    inventory_manager inventory_manager_obj;
    walk_in_customer walk_in_customer_obj;
    online_customer online_customer_obj;
    Store_Manager Store_Manager_obj;

    bool flag1 = 0;
    char menu;
    welcome();
    while (flag1 == 0)
    {
        flag = 0;
        while (flag == 0)
        {
            clearscreen();
            _menu();
            menu = _getch();

            if (menu == 97 || menu == 65)// for store MANAGEMENT
            {
                while (true)
                {
                    clearscreen();
                    boundry();
                    char str2[] = { "PRESS 1 TO ALLOCATE INVENTORY" };
                    myDrawTextWithFont(350, 150, 40, str2, black, skyblue);
                    char str3[] = { "PRESS 2 TO VIEW CUSTOMER DETAILS" };
                    myDrawTextWithFont(350, 200, 40, str3, black, skyblue);
                    char str4[] = { "PRESS 3 FOR BEST SELLING ITEM " };
                    myDrawTextWithFont(350, 250, 40, str4, black, skyblue);
                    char str5[] = { "PRESS 4 TO RETURN TO HOME SCREEN" };
                    myDrawTextWithFont(350, 300, 40, str5, black, skyblue);

                    char temp = _getch();

                    if (temp == 49) // ALLOCATE INVENTORY
                    {
                        clearscreen();
                        clear();
                        inventory_manager_obj.allocate(8, 400, "JEANS");
                        inventory_manager_obj.allocate(6, 500, "SHIRT");
                        inventory_manager_obj.allocate(4, 600, "UNDERGARMENTS");
                        inventory_manager_obj.allocate(2, 700, "JACKETS");
                        inventory_manager_obj.allocate(1, 800, "SHALWAR KURTA");
                        store_obj.view_product();

                        char str3[] = { " Press any key to continue.... " };
                        myDrawText(370, 450, 30, str3, white, NULL);
                        _getch();
                        clear();
                        clearscreen();
                    }
                    else if (temp == 50)//VIEW RECORD
                    {
                        //sleep(1);
                        clearscreen();
                        // Populating Customer
                        clear();
                        Store_Manager_obj.record_customer_details();// populate customer array from file // customer_details array willbe populated.
                        Store_Manager_obj.view_customer_details();// customer_details will be given on console

                        char str3[] = { " Press any key to continue.... " };
                        myDrawText(370, 450, 30, str3, white, NULL);
                        _getch();
                        clear();
                        clearscreen();

                    }
                    else if (temp == 51)//BEST SELLING ITEM
                    {
                        clearscreen();
                        clear();
                        cout << "BEST SELLING ITEM = " << Store_Manager_obj.best_selling_item();

                        char str3[] = { " Press any key to continue.... " };
                        myDrawText(370, 450, 30, str3, white, NULL);
                        _getch();
                        clear();
                        clearscreen();
                    }
                    else if (temp == 52)//return to home screen
                    {
                        break;
                    }
                    else
                    {
                        clearscreen();
                        boundry();
                        char str4[] = { "Invalid Key Entry!" };
                        myDrawTextWithFont(400, 200, 30, str4, black, red);
                        char str3[] = { " Press any key to continue.... " };
                        myDrawText(370, 450, 30, str3, white, NULL);
                        temp = _getch();
                        clear();
                        clearscreen();
                    }
                }
            }
            else if (menu == 98 || menu == 66)// for customer
            {
                while (true)
                {
                    clear();
                    clearscreen();
                    boundry();

                    char str6[] = { "PRESS 1 FOR WALK IN CUSTOMER" };
                    myDrawTextWithFont(340, 150, 40, str6, black, skyblue);
                    char str7[] = { "PRESS 2 FOR ONLINE CUSTOMER" };
                    myDrawTextWithFont(340, 200, 40, str7, black, skyblue);
                    char str5[] = { "PRESS 3 TO RETURN TO HOME SCREEN" };
                    myDrawTextWithFont(340, 250, 40, str5, black, skyblue);

                    char str = _getch();

                    if (str == 49)// WALK IN CUSTOMER
                    {
                        clearscreen();
                        boundry();
                        char str6[] = { "PRESS 1 TO BUY PRODUCTS" };
                        myDrawTextWithFont(340, 150, 40, str6, black, pink);
                        char str5[] = { "PRESS 2 TO RETURN TO HOME SCREEN" };
                        myDrawTextWithFont(340, 200, 40, str5, black, pink);
                        char ch = _getch();

                        if (ch == 49)
                        {
                            clearscreen();
                            clear();
                            for (fix = 0; fix < customer_details_size - 1; fix++)
                            {
                                walk_in_customer_obj.buy_product();
                            }
                            char str3[] = { " Press any key to continue.... " };
                            myDrawText(370, 450, 30, str3, white, NULL);
                            _getch();
                            clear();
                            clearscreen();
                        }
                        else if (ch == 50)
                        {
                            break;
                        }
                        else
                        {
                            clearscreen();
                            boundry();
                            char str4[] = { "Invalid Key Entry!" };
                            myDrawTextWithFont(400, 200, 30, str4, black, red);
                            char str3[] = { " Press any key to continue.... " };
                            myDrawText(370, 450, 30, str3, white, NULL);
                            str = _getch();
                        }
                    }
                    else if (str == 50)//ONLINE
                    {
                        clear();
                        clearscreen();
                        boundry();
                        char str5[] = { "PRESS 1 FOR VIEW ONLINE CUSTOMER DETAILS" };
                        myDrawTextWithFont(340, 150, 40, str5, black, cyan);
                        char str6[] = { "PRESS 2 FOR LOGIN" };
                        myDrawTextWithFont(340, 200, 40, str6, black, cyan);
                        char str8[] = { "PRESS 3 TO RETURN TO HOME SCREEN" };
                        myDrawTextWithFont(340, 250, 40, str8, black, cyan);
                        char str = _getch();

                        if (str == 49)
                        {
                            clear();
                            clearscreen();
                            online_customer_obj.record_online_customer_details();
                            online_customer_obj.view_online_customer_details();//check

                            char str3[] = { " Press any key to continue.... " };
                            myDrawText(370, 450, 30, str3, white, NULL);
                            _getch();
                            clear();
                            clearscreen();
                        }
                        else if (str == 50)//login
                        {
                            clear();
                            clearscreen();
                            online_customer_obj.login();
                            char str3[] = { " Press any key to continue.... " };
                            myDrawText(370, 450, 30, str3, white, NULL);
                            _getch();
                            clear();
                            clearscreen();
                            //online_customer_obj.buy_product();
                        }
                        else if (str == 51)
                        {
                            break;
                        }
                        else
                        {
                            clear();
                            clearscreen();
                            boundry();
                            char str4[] = { "Invalid Key Entry!" };
                            myDrawTextWithFont(400, 200, 30, str4, black, cyan);
                            char str3[] = { " Press any key to continue.... " };
                            myDrawText(370, 450, 30, str3, white, NULL);
                            str = _getch();
                            clear();
                            clearscreen();
                        }
                    }
                    else if (str == 51)//return to home screen
                    {
                        break;
                    }
                    else
                    {
                        clear();
                        clearscreen();
                        boundry();
                        char str4[] = { "Invalid Key Entry!" };
                        myDrawTextWithFont(400, 200, 30, str4, black, skyblue);
                        char str3[] = { " Press any key to continue.... " };
                        myDrawText(370, 450, 30, str3, white, NULL);
                        str = _getch();
                        clear();
                        clearscreen();
                    }
                }
            }
            else if (menu == 99 || menu == 67)// for exit
            {
                clearscreen();
                boundry();
                char str6[] = { "!THANK YOU!" };
                myDrawTextWithFont(340, 200, 80, str6, black, white);
                flag = 1;
                flag1 = 1;
            }
        }
    }
    _getch();
    clear();
    system("pause");
    return 0;
}