#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Employee {
    int skill, sumOfCosts, idxQ;
    vector<int> desiredProducts;

	Employee(int skill, vector<int> desiredProducts,int idx) : skill(skill),desiredProducts(desiredProducts), idxQ(idx),sumOfCosts(0){}
 
};

struct Product {
	int cost, amount;
};

class Heap {
private:
    vector<Employee*> heap;


    void heapifyUp(int idx) {
        int biggest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size() && compare(heap[biggest], heap[left])) {
            biggest = left;
        }

        if (right < size() && compare(heap[biggest], heap[right])) {
            biggest = right;
        }

        if (biggest != idx) {
            swap(idx, biggest);
            heapifyUp(biggest);
        }
    }

    void swap(int i, int j) {
        std::swap(heap[i], heap[j]);
    }

    

    static bool compare(Employee* a, Employee* b) {
        if (a->skill == b->skill) {
            return a->idxQ > b->idxQ; 
        }
        return a->skill < b->skill;
    }

public:
    void insert(Employee* employee) {
        heap.push_back(employee);
        int i = size() - 1;
        while (i > 2 && heap[(i - 1) / 2]->skill < heap[i]->skill) {
            std::swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
    }

    Employee* extractMax() {
        if (size() == 0) {
            return nullptr;
        }
        if (size() == 1) {
            Employee* root = heap[0];
            heap.clear();
            return root;
        }

        Employee* root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyUp(0);

        return root;
    }

    int size() {
        return heap.size();
    }
    bool empty() {
        return heap.empty();
    }
};


void runQueue(int r, vector<Product>& products, vector<Employee*>& employees) {
    Heap queue;
    for (auto* employee : employees) {
        queue.insert(employee);
    }

    while (r--) {
        int inQEmployees = queue.size();
		while (!queue.empty())
        for (int i = 0; i < inQEmployees; ++i) {
            Employee* employee = queue.extractMax();
            for (int product : employee->desiredProducts) {
                if (products[product - 1].amount > 0) {
                    employee->sumOfCosts += products[product - 1].cost;
                    employee->skill -= products[product - 1].cost;
                    products[product - 1].amount--;
                    break;
                }
            }
            if (employee->skill > 0) {
                queue.insert(employee);
            }
        }
    }

    for (auto* employee : employees) {
        std::cout << employee->sumOfCosts << std::endl;
    }

}


int main()
{

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int  n, p, r;
	cin >> n >> p >> r;
	vector<Product> products(p);
    vector<Employee*> employees(n);
	for (int i = 0; i < n; i++) {
		int m, help;
        cin >> help >> m;
        vector<int> temp(m);
		for (int j = 0; j < m; j++) {
            cin >> temp[j];
		}

        employees[i] = (new Employee(help, temp, i));
	}
	for (int i = 0; i < p; i++) {
		cin >> products[i].amount >> products[i].cost;
	}
	runQueue(r, products, employees);
    return 0;
}
