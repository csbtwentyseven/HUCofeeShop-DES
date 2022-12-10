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
		
		queue<int> createCashierQueue(int size){
			queue<int> q;
			for(int i = 0; i < size; i++){
				q.push(i);
			}
			
			return q;
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
		
		printQueue(arrival_times);
		cout << endl;
		printQueue(order_times);
		cout << endl;
		printQueue(brew_times);
		cout << endl;
		printQueue(prices);
		//cout << cashier << endl;
		//cout << orders <<endl;
		file.close();
	}
	
		void getCustomerTime(){
			while (!arrival_times.empty()){
				double customer_time = 0;
				customer_time = customer_time + order_times.front();
				//customer_time = customer_time + brew_times.front();
				customer_time = customer_time - arrival_times.front();

				order_times.pop();
				brew_times.pop();
				arrival_times.pop();
				customer_times.push(customer_time);
								
			}
			printQueue(customer_times);
		}
		
			void matchCashiers(){
				queue<int> cashierQueue = createCashierQueue(cashier);
				int ms = 0;
				
				while(ms<1000000){
					
					if(ms == arrival_times.front()){
						cout << "cashier is full";
						cashierQueue.pop();
						arrival_times.pop();
					}
					
					if(ms == (customer_times.front())){
						cout << "cashier is free";
						cashierQueue.push(1);
						customer_times.pop();
					}
			
					ms++;
				
				}
			}
	};

	
int main(){
	
	HUCofeeShop dataOrganizer;
	dataOrganizer.getInput();
	//dataOrganizer.matchCashiers();
	//dataOrganizer.getCustomerTime();

	
	return 0;
}
