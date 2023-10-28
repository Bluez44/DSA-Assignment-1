#include "main.h"

extern int MAXSIZE;

class imp_res : public Restaurant
{
	public:
		~imp_res() {
			// cout << endl ;
			while(cus_counter > 0) {
				customer* tmp = cus_current;
				// cout << "Delete " << tmp->name << " out of seat\n";
				cus_current = cus_current->next;
				tmp->next = NULL;
				tmp->prev = NULL;
				delete tmp;
				cus_counter--;
			}

			while(queue_counter > 0) {
				customer* tmp = queue_head;
				// cout << "Delete " << tmp->name << " out of queue\n";
				queue_head = queue_head->next;
				delete tmp;
				queue_counter--;
			}

			// cout <<  "The order of customers is: " ;
			while(cusOrder_head != NULL) {
				customer* tmp = cusOrder_head;
				// cout << tmp->name << " ";
				cusOrder_head = cusOrder_head->next;
				delete tmp;
			}

			// cout << endl;

			// cout << "Destructor completed\n";
		}
	private:
		int cus_counter = 0;
		int queue_counter = 0;
		bool add_to_order = true;
		bool add_to_queue = true;
		customer* cus_current = NULL;
		customer* queue_head = NULL;
		customer* queue_tail = NULL;
		customer* cusOrder_tail = NULL;
		customer* cusOrder_head = NULL;
		customer* cusOrder_current = NULL;
	public:	
		imp_res() {
			// cout << endl << "Implementing GOJO & SUKUNA'S RESTAURANT\n";
			};

		void print_cusOrder() {
			cout << "The order of customers is: ";
			customer* tmp = cusOrder_head;
			if(tmp == NULL) {
				cout << "Order is empty\n";
				return;
			}
			while(tmp != NULL) {
				cout << tmp->name << " " ;
				tmp = tmp->next;
			}
			tmp = NULL;
			cout << endl;
		}

		void print_queue() {
			if(queue_counter == 0) {
				// cout << "No one in queue\n";
				return;
			}
			// cout << "In queue has: " ;
			customer* tmp = queue_head;
			while(tmp != NULL) {
				tmp->print();
				tmp = tmp->next;
			}
			tmp = NULL;
			// cout << endl;
		}

		void print_list (int dir) {
			int i = cus_counter;
			customer* tmp = cus_current;
			if(dir > 0) {
				// cout << "From left to right list have: \n";
				while(i > 0) {
					// cout << "\t";
					tmp->print();
					tmp = tmp->next;
					i--;
				}
			}
			else if(dir < 0){
				// cout << "From rigth to left list have: \n";
				while(i > 0) {
					// cout << "\t";
					tmp->print();
					tmp = tmp->prev;
					i--;
				}
			}
			tmp = NULL;
			// cout << endl;
		}

		void addLeft(customer* &current, customer* &cus) {
			cus->next = current;
			cus->prev = current->prev;
			if(cus->prev != nullptr) current->prev->next = cus;
			current->prev = cus;
		}

		void addRight(customer* &current, customer* &cus) {
			cus->next = current->next;
			cus->prev = current;
			if(current->next != nullptr)
			current->next->prev = cus;
			current->next = cus;
		}
		
		customer* getAt(int n, customer* current) {
			customer* tmp = current;
			for(int i = 0; i < n; i ++) {
				tmp = tmp->next;
			}
			
			return tmp;
		}
		int getIndex(customer* current, string name) {
			customer* tmp = current;
			int index = 0;
			while(tmp->name != name) {
				tmp = tmp->next; index ++;
			}
			return index;
		}
		void swap(customer* a, customer* b) {
			int energy = a->energy;
			string name = a->name;
			a->energy = b->energy;
			a->name = b->name;
			b->energy = energy;
			b->name = name;
		}
		void insertionSort(customer* queue, int n, int incr, int &count) {  
    		for (int i = incr; i < n; i += incr) {  
        		for (int j=i; (j>=incr) ; j-=incr) { 
					customer* cus1 = getAt(j, queue);
					customer* cus2 = getAt(j-incr, queue);  
					int cus1_order = getIndex(cusOrder_head, cus1->name);
					int cus2_order = getIndex(cusOrder_head, cus2->name);
					// cout << cus2->energy << " " << cus1->energy << endl;
					if(abs(cus1->energy) > abs(cus2->energy)) {
						// swap(getAt(cus1_order, cusOrder_head), getAt(cus2_order, cusOrder_head));
            			swap(cus1, cus2);
            			count++;
						// cout << "swap " << count << endl;
					}
					else if(abs(cus1->energy) == abs(cus2->energy)) {
						if(cus1_order < cus2_order  ) {
							// swap(getAt(cus1_order, cusOrder_head), getAt(cus2_order, cusOrder_head));
							swap(cus1, cus2);
            				count++;
						}
					}
        		}   
    		}
			// customer *tmp = queue;
			// for(int i = 0; i <= n; i++) {
				// cout << tmp->energy << " " ;
			// 	tmp = tmp->next;
			// }
			// cout << endl;
		}

		int shellSort(customer* queue, int n) {
    		int count = 0;
    		for(int i = n/2; i > 2; i /=2) {
        		for(int j = 0; j < i; j++) {
					// cout << i << " " << n-j << " " << j << endl;
            		insertionSort(getAt(j,queue), n-j, i, count);
        		}
    		}
			// customer *tmp = queue;
			// for(int i = 0; i <= n; i++) {
				// cout << tmp->name << " " ;
			// 	tmp = tmp->next;
			// }
			// cout << endl << n << " " << 1 << endl;
    		insertionSort(queue, n, 1, count);
    		return count;
		}

		void addnewcus () {
			while(queue_counter > 0 && cus_counter < MAXSIZE) {
				add_to_order = false;
				// cout << "queue counter = " << queue_counter << endl;
				// cout << "queue head = " << queue_head->name << endl;
				customer* tmp = getAt(cus_counter, cusOrder_head);
				customer* newcus = getAt(getIndex(queue_head,tmp->name),queue_head);
				cout << newcus->name << " is add to list\n";
				RED(newcus->name, newcus->energy);
				
				if(queue_head->next == NULL) {
					delete queue_head;
					queue_head = queue_tail = NULL;
				}
				else {
					customer* tmp = queue_head;
					queue_head = queue_head->next;
					queue_head->prev = NULL;
					tmp->next = NULL;
					delete tmp;
				}
				queue_counter--;
				// print_queue();
			}
			add_to_order = true;
		}

		void isolateCustomerQueue(customer* tmp) {
			if(tmp == queue_tail) {
				// cout << "tail\n";
				if(queue_tail->prev != NULL) queue_tail = queue_tail->prev;
				queue_tail->next = NULL;
			}
			else {
				tmp->next->prev = tmp->prev;
			}
			if(tmp == queue_head) {
				// cout << "head\n";
				if(queue_head->next != NULL) queue_head = queue_head->next;
				queue_head->prev = NULL;
			}
			else {
				tmp->prev->next = tmp->next;
			}

		}

		void isolateCustomerOrder(customer* cusOrder) {
			if(cusOrder == cusOrder_tail) {
				cusOrder_tail = cusOrder_tail->prev;
				cusOrder_tail->next = NULL;
			}
			else {
				cusOrder->next->prev = cusOrder->prev;
			}
			if(cusOrder == cusOrder_head) {
				cusOrder_head = cusOrder_head->next;
				cusOrder_head->prev = NULL;
			}
			else {
				cusOrder->prev->next = cusOrder->next;
			}
		}

		void RED(string name, int energy)
		{
			// cout << "The new customer is " << name << " " << energy << endl;
			if(energy == 0) {
				// cout << "Customer's energy is 0\n"; 
				return;
			}

			customer *tmp = cus_current;
			for(int i = 0; i < cus_counter; i++) {
				if(tmp->name == name) {
					// cout << "This customer's : " << tmp->name << " " << energy << " has already in seat\n";
					return;
				}
				tmp = tmp->next;
			}
			if(add_to_queue == true) {
				tmp = queue_head;
				for(int i = 0; i < queue_counter; i++) {
					if(tmp->name == name) {
						// cout << "This customer's : " << tmp->name << " " << energy << " has already in queue\n";
						return;
					}
					tmp = tmp->next;
				}
			}
			tmp = NULL;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			

			if(cus_counter == 0) {
				cus_current = cus;
				// cout << "The first customer is: " << cus_current->name << " " << cus_current->energy << endl;
			}
			else if(cus_counter >= MAXSIZE/2 && cus_counter < MAXSIZE) {
				// cout << cus->name << " " << cus->energy << " have seat in different way\n";
				int RES = 0;
				int largest_sub = 0;
				bool flag = true;
				tmp = cus_current;
				customer *suitable_pos = NULL;
				for(int i = 0; i < cus_counter; i ++) {
					largest_sub = abs(cus->energy - tmp->energy);
					if(largest_sub > RES) {
						RES = largest_sub;
						suitable_pos = tmp;
					}
					if(tmp->next != NULL) tmp = tmp->next;
					else break;
				}
				RES = cus->energy - suitable_pos->energy; 
				if(RES < 0) {
					// cout << "Add left\n";
					addLeft(suitable_pos, cus);
				}
				else {
					// cout << "Add right\n";
					addRight(suitable_pos, cus);

				}
			}
			else if(cus_counter > 0 && cus_counter < MAXSIZE/2){
				if(cus->energy >= cus_current->energy) {
					// cout << cus->name << " " << cus->energy << " is added to the right of " << cus_current->name << endl;
					addRight(cus_current, cus);
				}
				else {
					// cout << cus->name << " " << cus->energy << " is added to the left of " << cus_current->name << endl;
					addLeft(cus_current, cus);
				}
				
			}
			else if(cus_counter == MAXSIZE && queue_counter < MAXSIZE && add_to_queue == true) {
				if(queue_counter == 0) queue_head = queue_tail = cus;
				else {
					queue_tail->next = cus;
					cus->prev = queue_tail;
					queue_tail = queue_tail->next;
				}
				queue_counter++;
				// cout << cus->name << " " << cus->energy << " is added to queue " << queue_counter <<  "\n";
				// return;
			}
			else add_to_order = false;
			
			if(cus_counter == 1) {
				// cout << "cus_counter is 1\n";
				if(cus_current->next == NULL) {
					cus_current->next = cus;
					cus->prev = cus_current;
				}
				else {
					cus_current->prev = cus;
					cus->next = cus_current;
				}
			}
			if(add_to_order == true) {
				customer* cusOrder = new customer(name, energy, NULL, NULL);
				if(cusOrder_head == NULL) {
					// cout << "The order list is empty\n";
					cusOrder_head = cusOrder_tail = cusOrder_current = cusOrder;
				}
				else {
					cusOrder_tail->next = cusOrder;
					cusOrder->prev = cusOrder_tail;
					cusOrder_tail = cusOrder_tail->next;
				} 
			}
			
			if(cus_counter < MAXSIZE) {
				cus_counter++;
				cus_current = cus;
			}
			// cout << "RED\n";
		}

		
		void BLUE(int num)
		{
			cout << "BLUE "<< num << endl;
			if(cus_current == NULL) {
				// cout << "No one in list\n";
				return;
			}
			if(num >= cus_counter) num = cus_counter;
			cout << "Order before BLUE\n"; print_cusOrder();
			cout << "List before BLUE \n"; print_list(3); cout << "Cus counter = " << cus_counter << endl;
			cout << "Queue before BLUE\n"; print_queue(); cout << "Queue counter = " << queue_counter << endl;
			while(num > 0) {
				customer* tmp = cus_current; 
				while(tmp->name != cusOrder_head->name) {
					tmp = tmp->next;
				}
				if(tmp->energy > 0) cus_current = tmp->next;
				else cus_current = tmp->prev;
				if(cus_counter == 1) {
					delete tmp;
					cus_current == NULL;
					// delete cusOrder_head;
					// cusOrder_head = cusOrder_tail = cusOrder_current = NULL;
					// cus_counter--;
					// num--;
				}
				else {
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					tmp->next = NULL;
					tmp->prev = NULL;
					// cout << "Delete " << tmp->name << " because of using meal too long\n";
					delete tmp;
					// cus_counter--;
					// cout << "Cus_counter = " << cus_counter << endl;
					// num--;
				}
					cusOrder_current = cusOrder_head;  
					// cout << "cus order heaed is " << cusOrder_head->name << endl;
					if(cusOrder_head->next != NULL) {
						// cout << cusOrder_head->name << " next is not NULL\n";
						cusOrder_head = cusOrder_head->next;
						cusOrder_head->prev = NULL;
						cusOrder_current->next = NULL;
						delete cusOrder_current;
						cusOrder_current = cusOrder_head;
					}
					else {
						delete cusOrder_head;
						cusOrder_head = cusOrder_tail = cusOrder_current = NULL;
					}
				
				cus_counter--; num--;
				
			}
			// cout << "Order after BLUE\n"; print_cusOrder(); 
			// cout << "List after BLUE\n"; print_list(3); cout << "Cus counter = " << cus_counter << endl;
			// cout << "Queue after BLUE\n"; print_queue();
			add_to_queue = false;
			addnewcus();
			// cout << "List after add new cus\n"; print_list(3); cout << "Cus counter = " << cus_counter << endl;
			add_to_queue = true;
		}

		

		void PURPLE()
		{
			if(queue_counter <= 1) {
				// cout << "No need to sort\n *PURPLE*\n"; 
				return;
			}
			int MAXENERGY = 0;
			int sort_count = 0;
			int index_onOrder = 0;
			customer* tmp = queue_head;
			customer* maxEnergy;
			// cout << "Queue before Shellsort:\n";
			while(tmp != NULL) {
				// cout << "\t" << tmp->name << " " << tmp->energy << endl;
				if(abs(tmp->energy) >= MAXENERGY) {
					MAXENERGY = abs(tmp->energy);
					maxEnergy = tmp;
				}
				tmp = tmp->next;
			}
			// cout << "List before shellsort " ; print_list(3);
			// cout << "Order before " ; print_cusOrder();
			index_onOrder = getIndex(cusOrder_head, queue_head->name);
			for(tmp = queue_head; tmp != maxEnergy; tmp = tmp->next) {
				sort_count++;
			}
			// cout << endl;
			// cout << "MAXENERGY: " << maxEnergy->energy << " " << maxEnergy->name << endl;
			// cout << "Index of it is: " << sort_count << endl;
			int to_blue = shellSort(queue_head, sort_count+1)%MAXSIZE;
			// cout << "Queue after Shellsort have: \n";
			// tmp = queue_head;
			// while(tmp != NULL) {
			// 	cout << "\t" << tmp->name << " " << tmp->energy << endl;
			// 	tmp = tmp->next;
			// }
			// tmp = queue_head;
			maxEnergy = getAt(index_onOrder, cusOrder_head);
			// cout << tmp->name << " " << maxEnergy->name << endl;
			for(int i = 0; i < sort_count; i++) {
				if(maxEnergy->name != tmp->name) {
					swap(getAt(getIndex(cusOrder_head, tmp->name), cusOrder_head), maxEnergy);
				}
				tmp = tmp->next;
				maxEnergy = maxEnergy->next;
			}
			// cout << "Order after shell sort: "; print_cusOrder() ;
			// cout << to_blue << endl;
			
			BLUE(to_blue);
			// cout << "list after shellsort: \n"; print_list(3);
			cout << "purple"<< endl;
		}

		void REVERSAL()
		{
			// cout << "reversal" << endl;
			if(cus_counter <= 1) return;
			customer* tmp = cus_current;
			// if(tmp == NULL) return;
			// cout << "List before reversal:\n";
			// print_list(3);

			
			customer* cus_next;
			customer* cus_prev;
			cus_prev = cus_current;
			cus_next = cus_prev->next;
			for(int i = 0; i < cus_counter; i++) {
				if(cus_prev->energy > 0) {
					if(cus_next->energy < 0) {
						while(cus_next != cus_prev && cus_next->energy < 0) cus_next = cus_next->next;
					}
					// cout << "swap fufushi " << cus_next->name << " " << cus_prev->name << endl;
						if(cus_prev == cus_next) break;
					if(cus_current == cus_prev) cus_current = cus_next;
					swap(cus_next, cus_prev);
					cus_next = cus_next->next;
					if(cus_prev == cus_next) break;
					
				}
				cus_prev = cus_prev->prev;
				if(cus_prev == cus_next) break;
			}

			cus_prev = cus_current;
			cus_next = cus_prev->next;
			for(int i = 0; i < cus_counter; i++) {
				if(cus_prev->energy < 0) {
					if(cus_next->energy > 0) {
						while(cus_next != cus_prev && cus_next->energy > 0) cus_next = cus_next->next;
					}
					// cout << "swap furei " << cus_next->name << " " << cus_prev->name << endl;
						if(cus_prev == cus_next) break;
					if(cus_current == cus_prev) cus_current = cus_next;
					swap(cus_next, cus_prev);
					cus_next = cus_next->next;
					if(cus_prev == cus_next) break;
					
				}
				cus_prev = cus_prev->prev;
				if(cus_prev == cus_next) break;
			}

			// cout << "List after reversal:\n";
			// print_list(3);

		}

		void UNLIMITED_VOID()
		{
			// cout << endl;
			// print_list(3);
			if(cus_counter <=4) return;
			int sum1 = 0, sum2 = 10000;
			int element_counter = 0, sublist_element_counter = 0;
			customer* current = cus_current;
			customer* current2 = NULL;
			customer* sublist_key = NULL;
			customer* sublist_head = NULL, *sublist_tail = NULL;
			customer* sublist_smallest = NULL;
			for(int i = 0; i < cus_counter ; i++) {
				sum1 = 0;
				element_counter = 0;
				current2 = current->next;
				for(int j = 1; j < cus_counter*2 -1 && element_counter < cus_counter; j++) {
					sum1 += current2->energy;
					element_counter++;
					if(sum1 <= sum2 && element_counter >=4) {
						if(sum1 == sum2 && element_counter > sublist_element_counter) {
							sublist_element_counter = element_counter;
						}
						else if(sum1 < sum2) {
							sum2 = sum1;
							sublist_element_counter = element_counter;
						}
						sublist_key = current2;
					}
					current2 = current2->next;
				}
				current = current->next;
			}
			// cout << "key = " << sublist_key->name << endl;
			for(int i = 0; i < sublist_element_counter; i++) {
				if(i == 0) {
					sublist_head = sublist_tail = sublist_smallest = new customer(*sublist_key);
				}
				else if(i == 1) {
					sublist_head->prev = new customer(*sublist_key);
					sublist_head = sublist_head->prev;
					sublist_head->next = sublist_tail;
					sublist_tail->next = sublist_head;
					sublist_head->prev = sublist_tail;
				}
				else {
					sublist_head->prev = new customer(*sublist_key);
					sublist_head->prev->next = sublist_head;
					sublist_head = sublist_head->prev;
					sublist_tail->next = sublist_head;
					sublist_head->prev = sublist_tail;
				}
				if(sublist_head->energy <= sublist_smallest->energy) sublist_smallest = sublist_head;
				sublist_key = sublist_key->prev;
			}
			for(int i = 0; i < sublist_element_counter; i ++) {
				sublist_smallest->print();
				sublist_key = sublist_smallest;
				sublist_smallest = sublist_smallest->next;
				if(sublist_key->prev != NULL) sublist_key->prev->next = NULL;
				sublist_key->prev = NULL;
				if(sublist_key->next != NULL) sublist_key->next->prev = NULL;
				sublist_key->next = NULL;
				delete sublist_key;
			}
			sublist_head = sublist_key = sublist_smallest = sublist_tail = NULL;

			// cout << "\nsum2 = " << sum2 << " counter = " << sublist_element_counter << endl;
			
			// cout << "unlimited_void" << endl;
		}

		void calc_sum_of_energy(int &sum_of_Jujutsushi, int &sum_of_Jurei,int count,int &num_of_Jujutsushi, int &num_of_Jurei, customer* tmp) {
			if(tmp == NULL) return;
			for(int i = 0; i < count; i++) {
				// cout << tmp->name << " " << tmp->energy << endl;
				if(tmp->energy > 0) {
					sum_of_Jujutsushi += tmp->energy;
					num_of_Jujutsushi++;
				}
				else {
					sum_of_Jurei += tmp->energy;
					num_of_Jurei++;
				}
				// cout << sum_of_Jujutsushi << "\t" << sum_of_Jurei << endl;
				// cout << num_of_Jujutsushi << "\t" << num_of_Jurei << endl;
				tmp = tmp->next;
			}
		}

		
		void DOMAIN_EXPANSION()
		{
			int sum_of_Jujutsushi = 0, sum_of_Jurei = 0;
			int num_of_Jujutsushi = 0, num_of_Jurei = 0;
			customer* tmp;	
			
			// cout << "Calculate sum of energy in list\n";
			tmp = cus_current;
			calc_sum_of_energy(sum_of_Jujutsushi, sum_of_Jurei, cus_counter, num_of_Jujutsushi, num_of_Jurei, tmp);

			// cout << "Calculate sum of energy in queue\n";
			tmp = queue_head;
			calc_sum_of_energy(sum_of_Jujutsushi, sum_of_Jurei, queue_counter, num_of_Jujutsushi, num_of_Jurei, tmp);
			// cout << sum_of_Jujutsushi << " " << sum_of_Jurei << endl;
			// cout << num_of_Jujutsushi << " " << num_of_Jurei << endl;
			if(num_of_Jujutsushi == 0 || num_of_Jurei == 0) return;
			// print_list(3);
			// print_queue();
			if(sum_of_Jujutsushi < abs(sum_of_Jurei)) {  
				// cout << "delete fufutsu-shi\n";   					// Xoa chu thuat su
				customer* cusOrder = cusOrder_tail; 
				while(cusOrder != NULL) {
					if(cusOrder->energy > 0) {
						// cout << endl <<  cusOrder->name << "-" << cusOrder->energy << " " ;
						// cusOrder->print();
						// int index = getIndex(cusOrder_head, cusOrder->name); cout << index << " " << endl;
						tmp = queue_tail;
						while(tmp != NULL) {    // kiem tra cusOrder->name co tren queue khong
							if(tmp->name == cusOrder->name) {   
								// cout  << "\nFOUND " << tmp->name << " " << cusOrder->energy << " on queue\n " ;
								isolateCustomerQueue(tmp);
								customer* tmp2 = tmp; 
								if(tmp == queue_tail) queue_tail = queue_tail->prev;
								if(tmp == queue_head) tmp = queue_head = queue_tail = NULL;
								else tmp = tmp->prev;
								tmp2->next = tmp2->prev = NULL;
								delete tmp2;
								queue_counter--;
								break;
							}
							tmp = tmp->prev;
						}
						if(tmp == NULL) {
							tmp = cus_current;
							for(int i = 0; i < cus_counter; i++) {
								if(tmp->name == cusOrder->name) {
									// cout  << "\nFOUND " << tmp->name << " " << cusOrder->energy << " on list\n " ;
									isolateCustomerQueue(tmp);
									customer* tmp2 = tmp->prev;
									if(cus_current == tmp) cus_current = tmp2;
									tmp->next = tmp->prev = NULL;
									delete tmp;
									cus_counter--;
									tmp = tmp2;
									break;
								}
								tmp = tmp->prev;
							}
						}
						isolateCustomerOrder(cusOrder);
						customer* prev_cusOrder = cusOrder->prev; 
						cusOrder->next  = cusOrder->prev = NULL;
						delete cusOrder;
						cusOrder = prev_cusOrder;
					}
					else cusOrder = cusOrder->prev;
				}
				// cout << cus_counter << " " << queue_counter << endl;
			}
			else { 
				// cout << "delete furei\n";   					// Xoa oan linh
				customer* cusOrder = cusOrder_tail; 
				while(cusOrder != NULL) {
					if(cusOrder->energy < 0) {
						// cout << endl <<  cusOrder->name << "-" << cusOrder->energy << " " ;
						// cusOrder->print();
						// int index = getIndex(cusOrder_head, cusOrder->name); cout << index << " " << endl;
						tmp = queue_tail;
						while(tmp != NULL) {    // kiem tra cusOrder->name co tren queue khong
							if(tmp->name == cusOrder->name) {   
								// cout << "\nFOUND " << tmp->name << " " << cusOrder->energy << " on queue\n " ;
								isolateCustomerQueue(tmp);
								customer* tmp2 = tmp; 
								if(tmp == queue_tail) queue_tail = queue_tail->prev;
								if(tmp == queue_head) tmp = queue_head = queue_tail = NULL;
								else tmp = tmp->prev;
								tmp2->next = tmp2->prev = NULL;
								delete tmp2;
								queue_counter--;
								break;
							}
							tmp = tmp->prev;
						}
						if(tmp == NULL) {
							tmp = cus_current;
							for(int i = 0; i < cus_counter; i++) {
								if(tmp->name == cusOrder->name) {
									// cout << "\nFOUND " << tmp->name << " " << cusOrder->energy << " on list\n " ;
									isolateCustomerQueue(tmp);
									customer* tmp2 = tmp->prev;
									if(cus_current == tmp) cus_current = tmp2;
									tmp->next = tmp->prev = NULL;
									delete tmp;
									cus_counter--;
									tmp = tmp2;
									break;
								}
								tmp = tmp->prev;
							}
						}
						isolateCustomerOrder(cusOrder);
						customer* prev_cusOrder = cusOrder->prev; 
						cusOrder->next  = cusOrder->prev = NULL;
						delete cusOrder;
						cusOrder = prev_cusOrder;
					}
					else cusOrder = cusOrder->prev;
				}
				// cout << cus_counter << " " << queue_counter << endl;
			}
			add_to_queue = false;
			addnewcus();
			add_to_queue = true;
			// cout << endl;
			// print_list(3);
			cout << "\ndomain_expansion (not completed)" << endl;
		}
		void LIGHT(int num)
		{
			// cout << endl;
			// if(num != 0) {
			// 	print_list(num);
			// }
			// else print_queue();
			cout << "LIGHT " << num << endl;
		}
		
};