#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
using namespace std;
class HUCofeeShop{
	public:
		ifstream file;
		string line;
		
		int cashier;
		int orders;
		
		queue<int> arrival_times;
		queue<int> order_times;
		queue<int> brew_times;
		queue<int> prices;
		queue<int> customer_times;
		queue<int> cashierQueue;
		queue<int> customerQueue;

		
		void createCashierQueue(int size){
	
			for(int i = 0; i < size; i++){
				cashierQueue.push(1);
			}
			
		}
		
		void createCustomerQueue(int size){
	
			for(int i = 0; i < size; i++){
				customerQueue.push(1);
			}
			
		}
		
		
		void printQueue(queue<int> q)
		{
			//printing content of queue 
			while (!q.empty()){
				cout<<" "<<q.front();
				q.pop();
			}
		
		}
		
		
		void getInput(){
		file.open("input.txt");
		int index = 0;
		
		while(file.good()){
			getline(file, line);
			//cout << line << endl;
			
			switch(index){
				case 0:
					cashier = stoi(line);
					break;
					
				case 1:
					orders = stoi(line);
					break;
				
				default:
					    istringstream iss(line);
						  string s;
						  int index = 0;
						  while ( getline(iss, s, ' ' ) ) {
						    //printf( "%s\n", s.c_str() );
						    switch(index){
						    	case 0:
								{
									string arrival_time = s.c_str();
									double arrival_time_seconds = stod(arrival_time);
									int arrival_time_ms = (arrival_time_seconds + 0.001) * 100;
									
						    		arrival_times.push(arrival_time_ms); // stod - string to double
						    		break;
								}
						    	
						   		case 1:
								   {
						   			string order_time = s.c_str();
						    		double order_time_seconds = stod(order_time);
									int order_time_ms = (order_time_seconds + 0.001) * 100;
									
						    		order_times.push(order_time_ms); // stod - string to double
						    		break;
								   }
								   
								case 2:
								   {
						   			string brew_time = s.c_str();
						    		double brew_time_seconds = stod(brew_time);
									int brew_time_ms = (brew_time_seconds + 0.001) * 100;
									
						    		brew_times.push(brew_time_ms); // stod - string to double
						    		break;
								   }
								
								case 3:
								   {
						   			string price = s.c_str();
						    		double price_dollars = stod(price);
									int price_cents = (price_dollars + 0.001) * 100;
									
						    		prices.push(price_cents); // stod - string to double
						    		break;
								   }
							
							}
							index++;
						  }	
			}
			index++;
		}
		
		/*
		printQueue(arrival_times);
		cout << endl;
		printQueue(order_times);
		cout << endl;
		printQueue(brew_times);
		cout << endl;
		printQueue(prices);
		cout << cashier << endl;
		cout << orders <<endl;
		*/
		createCashierQueue(cashier);
		createCustomerQueue(orders);
		file.close();
	}
	
		void getCustomerTime(){
				queue<int> order_times2 = order_times;
				queue<int> brew_times2 = brew_times;
				queue<int> arrival_times2 = arrival_times;
			while (!arrival_times2.empty()){
				int customer_time = 0;
				customer_time = customer_time + order_times2.front();
				//customer_time = customer_time + brew_times.front();
				customer_time = customer_time + arrival_times2.front();

				order_times2.pop();
				brew_times2.pop();
				arrival_times2.pop();
				customer_times.push(customer_time);
								
			}
			//printQueue(customer_times);
		}
		
			void matchCashiers(){
				int ms = 0;

				
				while(ms<100000){
						
					if(ms == arrival_times.front()){
						cout << "cashier is full" << ms << endl;
						cashierQueue.pop();
						arrival_times.pop();
						printQueue(cashierQueue);
		
					}
					
					if(ms == (customer_times.front())){
						cout << "cashier is free" << ms <<endl;
						cashierQueue.push(1);
						customer_times.pop();
						printQueue(cashierQueue);

					}
					
					ms++;
					//cout << ms << endl;
					}
		
			}
	};

	
int main(){
	
	HUCofeeShop dataOrganizer;
	dataOrganizer.getInput();
	dataOrganizer.getCustomerTime();
	dataOrganizer.matchCashiers();

	
	return 0;
}
