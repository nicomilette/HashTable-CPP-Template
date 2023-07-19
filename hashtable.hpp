using namespace cop4530;

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
   if (n > max_prime)
   {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
   }
   if (n == max_prime)
   {
      return max_prime;
   }
   if (n <= 1)
   {
      std::cerr << "** input too small \n";
      return 0;
   }

   // now: 2 <= n < max_prime
   std::vector <unsigned long> v (n+1);
   setPrimes(v);
   while (n > 2)
   {
      if (v[n] == 1)
         return n;
      --n;
   }

   return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
   int i = 0;
   int j = 0;

   vprimes[0] = 0;
   vprimes[1] = 0;
   int n = vprimes.capacity();

   for (i = 2; i < n; ++i)
      vprimes[i] = 1;

   for( i = 2; i*i < n; ++i)
   {
      if (vprimes[i] == 1)
         for(j = i + i ; j < n; j += i)
            vprimes[j] = 0;
   }
}

template <typename K, typename V>
size_t HashTable<K,V>::size() const
{
   return currentSize;
}

template <typename K, typename V>
HashTable<K,V>::HashTable(size_t size) : currentSize{0}, table{prime_below(size)} {}

template <typename K, typename V>
HashTable<K,V>::~HashTable()
{
    makeEmpty();
}

template <typename K, typename V>
void HashTable<K,V>::makeEmpty()
{
    for (auto & itr : table) itr.clear();
    currentSize = 0;
}

template <typename K, typename V>
void HashTable<K,V>::clear()
{
    makeEmpty();
}


/*
template <typename K, typename V>
void HashTable<K, V>::dump() {
   cout << "----- Beginning the dump -----\n";
    for (size_t i = 0; i < table.size(); ++i) {
        if (!table[i].empty()) {
            auto it = table[i].begin();
            cout << it->first << " " << it->second;
            ++it;
            for (; it != table[i].end(); ++it) {
                cout << " | " << it->first << " " << it->second;
            }
            cout << endl;
        }
    }
   cout << "----- End -----\n";
}
*/

template <typename K, typename V>
void HashTable<K, V>::dump() {
    cout << "----- Beginning the dump -----" << endl;
    for (size_t i = 0; i < table.size(); ++i) {
        if (!table[i].empty()) {
            vector<pair<K, V>> pairs;
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                pairs.push_back(*it);
            }
            sort(pairs.begin(), pairs.end());
            auto it = pairs.begin();
            cout << it->first << " " << it->second;
            ++it;
            for (; it != pairs.end(); ++it) {
                cout << " | " << it->first << " " << it->second;
            }
            cout << endl;
        }
    }
    cout << "----- End -----" << endl;
}



template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) {
    if (contains(kv.first)) // if key already exists, don't add
        return false;

    size_t index = myhash(kv.first);
    table[index].push_front(kv);
    ++currentSize;

    if (currentSize > table.size())
        rehash();

    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv) {
    if (contains(kv.first)) {
        return false;
    }
    
    size_t index = myhash(kv.first);
    table[index].push_back(std::move(kv));
    ++currentSize;

     if (currentSize > table.size())
        rehash();
    return true;
}


template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K & x) const{
    static std::hash<K> hf;
    return hf(x) % table.size();
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K& x)
{
  size_t bucket = myhash(x); // get the bucket where x should be stored
  for(const std::pair<K,V>& kv : table[bucket]) { // for each key-value pair in the bucket
    if(kv.first == x) { // if the key x is found in the bucket
      return true;
    }
  }
  return false; // if x is not found in any bucket
}


template<typename K, typename V>
string HashTable<K, V>::getValue(const K &x) const
{
      size_t bucket = myhash(x);
      for(const std::pair<K,V>& kv : table[bucket]) {
            if(kv.first == x) { 
                  return kv.second;
            }
      }
}

template<typename K, typename V>
void HashTable<K, V>::update(const std::pair<K,V> &kv) 
{
      size_t bucket = myhash(kv.first);
      for(std::pair<K,V>& kv1 : table[bucket]) { 
            if(kv1.first == kv.first) { 
                    kv1.second = kv.second;
                    break;
            }
      }
}




template <typename K, typename V>
void HashTable<K,V>::rehash() {
    size_t new_size = prime_below(table.size() * 2); 
    vector<list<std::pair<K, V>>> new_table(new_size); 
    for (auto& lst : table) { 
        for (auto& kv : lst) { 
            size_t idx = myhash(kv.first) % new_size; 
            new_table[idx].push_back(kv);
        }
    }
    table = std::move(new_table); 
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> & kv) const {
    size_t index = myhash(kv.first);
    for (auto & entry : table[index]) {
        if (entry.first == kv.first && entry.second == kv.second) {
            return true;
        }
    }
    return false;
}


template<typename K, typename V>
bool HashTable<K, V>::remove(const K & k) {
    size_t index = myhash(k);
    auto it = table[index].begin();
    while (it != table[index].end()) {
        if (it->first == k) {
            table[index].erase(it);
            --currentSize;
            return true;
        }
        ++it;
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        K k;
        V v;
        if (iss >> k >> v) {
            std::pair<K, V> kv(k, v);
            insert(kv);
        }
    }
    infile.close();
    return true;
}


template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return false;
    }
    for (auto& list : table) {
        for (auto& kv : list) {
            outfile << kv.first << " " << kv.second << std::endl;
        }
    }
    outfile.close();
    return true;
}
