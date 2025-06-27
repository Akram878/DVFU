#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono> //time
#include <functional>  // لإضافة std::hash

using namespace std;

template <typename K, typename V>
class HashMap {
private:
    static const int SIZE = 1000;
    vector<pair<K, V>> table[SIZE]; //  if we want multi hash map we have to use vector in second value


    int hash(K key) {
        std::hash<K> hasher;
        return hasher(key) % SIZE;
    }

public:

    void put(K key, V value) {
        int index = hash(key);
        for (auto &pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back(make_pair(key, value)); // إضافة عنصر جديد 11 يمكن ان نستخدم {}
    }


    V get(K key) {
        int index = hash(key);
        for (auto &pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw runtime_error("Key not found");
    }


    void remove(K key) {
        int index = hash(key);
        auto &bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return;
            }
        }
    }


    bool containsKey(K key) {
        int index = hash(key);
        for (auto &pair : table[index]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }


    int size() {
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            count += table[i].size();
        }
        return count;
    }


    void display() {

        cout<<"{";
        for (int i = 0; i < SIZE; i++) {
            if (!table[i].empty()) {
                for (auto &pair : table[i]) {
                    cout <<  pair.first << ": " << pair.second << ",";
                }

            }

        }
        cout<<"}"<<endl;
    }


    void testCollisionsAndPerformance() {

        put("abc", 1);
        put("acb", 2);
        put("xyz", 3);


        auto start = chrono::high_resolution_clock::now();
        put("apple", 5);
        put("banana", 3);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Time taken for 2 put operations: " << diff.count() << " seconds" << endl;


        cout << "Size after adding elements: " << size() << endl;
    }
};

int main() {
    HashMap<string, int> map;


    map.put("apple", 5);
    map.put("banana", 3);
    map.put("orange", 7);


    try {
        cout << "apple: " << map.get("apple") << endl;
    } catch (const exception &e) {
        cout << e.what() << endl;
    }

    cout << "Contains 'banana': " << map.containsKey("banana") << endl;


    map.remove("apple");


    cout << "Contains 'apple': " << map.containsKey("apple") << endl;


    map.display();


    cout << "Size: " << map.size() << endl;


    map.testCollisionsAndPerformance();

    return 0;
}
