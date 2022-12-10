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
		
		queue<double> arrival_times;
		queue<double> order_times;
		queue<double> brew_times;
		queue<double> prices;
		queue<double> customer_times;
		
		queue<int> createCashierQueue(int size){
			queue<int> q;
			for(int i = 0; i < size; i++){
				q.push(i);
			}
			
			return q;
		}
		
		void printQueue(queue<double> q)
		{
			//printing content of queue 
			while (!q.empty()){
				cout<<" "<<q.front();
				q.pop();
			}
		
		}
		
		void printIntQueue(queue<int> q)
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
						    		arrival_times.push(stod(arrival_time)); // stod - string to double
						    		break;
								}
						    	
						   		case 1:
								   {
						   			string order_time = s.c_str();
						    		order_times.push(stod(order_time));
						    		break;
								   }
								   
								case 2:
								   {
						   			string brew_time = s.c_str();
						    		brew_times.push(stod(brew_time));
						    		break;
								   }
								
								case 3:
								   {
						   			string price = s.c_str();
						    		prices.push(stod(price));
						    		break;
								   }
							
							}
							index++;
						  }	
			}
			index++;
		}
		
		//cout << cashier << endl;
		//cout << orders <<endl;
		file.close();
	}
	
		void getCustomerTime(){
			while (!arrival_times.empty()){
				double customer_time = 0;
				customer_time = customer_time + order_times.front();
				customer_time = customer_time + brew_times.front();
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
			printIntQueue(cashierQueue);
		}
};

	
int main(){
	
	HUCofeeShop dataOrganizer;
	dataOrganizer.getInput();
	dataOrganizer.matchCashiers();
	//dataOrganizer.getCustomerTime();

	
	return 0;
}
