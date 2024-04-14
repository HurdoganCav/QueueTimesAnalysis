#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    // Kullanıcıdan sıradaki insan sayısını girmesini ister.
    int num_people;
    cout << "Enter the number of people in the queue: ";
    cin >> num_people;

    // Her kişi için 30-300 arasında rastgele prosedür süreleri oluşturur ve bunları "procedure_times" adlı bir vektörde saklar.
    vector<int> procedure_times(num_people);
    srand(time(NULL));
    for (int i = 0; i < num_people; i++) {
        procedure_times[i] = rand() % 271 + 30;
    }

    // "queue_list" adlı bir liste veri yapısı kullanarak bir yığın oluşturur ve herkesi yığına ekler.
    vector<int> queue_list(num_people);
    for (int i = 0; i < num_people; i++) {
        queue_list[i] = i + 1;
    }

    // Yığın üzerinde döngü oluşturur ve her kişi için bekleme süresini, prosedür süresini ve toplam harcanan süreyi hesaplar
    int total_time = 0;
    vector<int> wait_times(num_people);
    vector<int> total_times(num_people);
    for (int i = 0; i < num_people; i++) {
        int person = queue_list[i];
        int wait_time = total_time;
        int total_time_spent = wait_time + procedure_times[person - 1];
        total_time += procedure_times[person - 1];
        wait_times[person - 1] = wait_time;
        total_times[person - 1] = total_time_spent;
        cout << "Person " << person << ": Wait time = " << wait_time << ", Procedure time = " << procedure_times[person - 1] << ", Total time spent = " << total_time_spent <<" (FIFO) "<<endl;
    }

    // Averaj toplam harcanan zaman hesapkanır FIFO için
    double avg_total_time = (double) accumulate(total_times.begin(), total_times.end(), 0) / num_people;
    cout << "Average total time spent = " << avg_total_time << endl;

    // "queue_array" adlı bir dizi veri yapısı kullanarak bir yığın oluşturur ve her kişiyi yığına ekler.
    int queue_array[num_people];
    for (int i = 0; i < num_people; i++) {
        queue_array[i] = i + 1;
    }

    // Prosedür süresine göre yığındaki sıralamayı, prosedür süresi en az olan kişinin yığının en üstünde olduğu şekilde sıralar.
    sort(queue_array, queue_array + num_people, [&](int a, int b) {
        return procedure_times[a - 1] < procedure_times[b - 1];
    });

    // Yığın üzerinde döngü oluşturur ve her kişi için bekleme süresini ve toplam harcanan süreyi hesaplar.
    int total_time_pq = 0;
    vector<int> wait_times_pq(num_people);
    vector<int> total_times_pq(num_people);
    for (int i = 0; i < num_people; i++) {
        int person = queue_array[i];
        int wait_time = total_time_pq;
        int total_time_spent = wait_time + procedure_times[person - 1];
        total_time_pq += procedure_times[person - 1];
        wait_times_pq[person - 1] = wait_time;
        total_times_pq[person - 1] = total_time_spent;
       cout << "Person " << person << ": Wait time = " << wait_time << ", Procedure time = " << procedure_times[person - 1] << ", Total time spent = " << total_time_spent <<" (PQ) "<<endl;
    }

    // Harcanan averaj toplam zaman PQ için hesaplanır.
    double avg_total_time_pq = (double) accumulate(total_times_pq.begin(), total_times_pq.end(), 0) / num_people;
    cout << "Average total time spent on the priority queue = " << avg_total_time_pq << endl;

    // FIFO kuyruğunda ve öncelik kuyruğunda her bir kişi için harcanan süreleri karşılaştırır ve öncelik kuyruğunda daha uzun süre bekleyen insanları, prosedür süresi ve kuyruk numarası ile birlikte görüntüler.
    vector<int> longer_wait_pq;
    for (int i = 0; i < num_people; i++) {
        if (wait_times_pq[i] > wait_times[i]) {
            longer_wait_pq.push_back(i + 1);
        }
    }
    if (longer_wait_pq.size() > 0) {
        cout << "People who waited longer on the priority queue: ";
        for (int i = 0; i < longer_wait_pq.size(); i++) {
            cout << "Person " << longer_wait_pq[i] << " (Procedure time = " << procedure_times[longer_wait_pq[i] - 1] << ", Queue number = " << (find(queue_list.begin(), queue_list.end(), longer_wait_pq[i]) - queue_list.begin()) + 1 << ")";
            if (i != longer_wait_pq.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    return 0;
}