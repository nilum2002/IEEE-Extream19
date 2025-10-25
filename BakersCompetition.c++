#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to get prime factorization
pair<long long, long long> getSemiprimeFactors(long long n) {
    long long original = n;
    long long first = -1;
    
    // Check for factor 2
    if (n % 2 == 0) {
        first = 2;
        n /= 2;
        if (n == 2) return {2, 2}; // 4 = 2*2
        if (n % 2 == 0) return {-1, -1}; // More than 2 factors of 2
        if (n > 1) {
            // Check if remaining is prime
            bool isPrime = true;
            for (long long i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return {2, n};
        }
        return {-1, -1};
    }
    
    // Check for odd factors
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            first = i;
            n /= i;
            if (n == i) return {i, i}; // Perfect square of prime
            if (n % i == 0) return {-1, -1}; // More than 2 factors
            
            // Check if remaining is prime
            bool isPrime = true;
            for (long long j = 3; j * j <= n; j += 2) {
                if (n % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return {i, n};
            return {-1, -1};
        }
    }
    
    return {-1, -1}; // n is prime itself, not a semiprime
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        long long l, r;
        cin >> l >> r;
        
        // Map: prime -> count of semiprimes containing this prime
        unordered_map<long long, long long> primeCount;
        vector<pair<long long, long long>> semiprimes;
        
        for (long long i = l; i <= r; i++) {
            auto [p1, p2] = getSemiprimeFactors(i);
            if (p1 != -1) {
                semiprimes.push_back({p1, p2});
                primeCount[p1]++;
                if (p2 != p1) {
                    primeCount[p2]++;
                }
            }
        }
        
        long long count = 0;
        
        // For each prime, count pairs
        for (auto& [prime, cnt] : primeCount) {
            count += cnt * (cnt - 1) / 2;
        }
        
        // Subtract overcounted pairs (those that share BOTH primes)
        for (int i = 0; i < semiprimes.size(); i++) {
            for (int j = i + 1; j < semiprimes.size(); j++) {
                if (semiprimes[i].first == semiprimes[j].first && 
                    semiprimes[i].second == semiprimes[j].second) {
                    count--;
                }
            }
        }
        
        cout << count << endl;
    }
    
    return 0;
}