#include <iostream>

using namespace std;

// Performinf (a + b with modular)
long long modular_additions(long long a, long long b, long long prime_modulus) {
    
    return ((a % prime_modulus) + (b % prime_modulus)) % prime_modulus;
}

// Performsing (a - b) with modular
long long modular_substractions(long long a, long long b, long long prime_modulus) {
    
    return ((a % prime_modulus) - (b % prime_modulus) + prime_modulus) % prime_modulus;
}

// Performsing (a  b) with modular
long long modular_multiplication(long long a, long long b, long long prime_modulus) {
    
    return ((a % prime_modulus) * (b % prime_modulus))  % prime_modulus;
}

// Computes power with modular
long long modular_pow(long long base, long long power, long long prime_modulus) {
    
    long long res = 1;
    
    base = base % prime_modulus;
    
    while (power > 0) {
        
        if (power % 2 == 1) {
            
            res = modular_multiplication(res, base, prime_modulus);
        }
        base = modular_multiplication(base, base, prime_modulus);
        
        power = power / 2;
    }
    return res;
}


// Computing the sum of points 
pair<long long, long long> compute_point_sum(long long curve_a, long long curve_b, long long prime,
                                            long long px, long long py, long long qx, long long qy) {
    
    if (px == qx && modular_additions(py, qy, prime) == 0) {
        return {-1, -1}; // Indicates point at infinity
    }

    long long slope;
    if (px == qx && py == qy) { 
    
        // Slope = (3 * px^2 + curve_a) / (2 * py) mod prime
        long long num = modular_additions(modular_multiplication(3, modular_multiplication(px, px, prime), prime), curve_a, prime);

        long long den = modular_multiplication(2, py, prime);

        slope = modular_multiplication(num, modular_pow(den, prime-2, prime), prime);
    } else { 
        // Slope = (qy - py) / (qx - px) mod prime
        long long num = modular_substractions(qy, py, prime);

        long long den = modular_substractions(qx, px, prime);

        slope = modular_multiplication(num, modular_pow(den, prime-2, prime), prime);
    }

    // x3 = slope^2 - px - qx mod prime
    long long x3 = modular_substractions(modular_multiplication(slope, slope, prime), modular_additions(px, qx, prime), prime);
    
    // y3 = slope * (px - x3) - py mod prime
    
    long long y3 = modular_substractions(modular_multiplication(slope, modular_substractions(px, x3, prime), prime), py, prime);

    return {x3, y3};
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    int num_test_cases;
    cin >> num_test_cases;

    for (int t = 0; t < num_test_cases; ++t) {


        long long curve_a, curve_b, prime, px, py, qx, qy;

        //taking the inputs
        cin >> curve_a >> curve_b >> prime >> px >> py >> qx >> qy;

        // Computinng the rsult
        auto result = compute_point_sum(curve_a, curve_b, prime, px, py, qx, qy);

        // Output for the infinity 
        if (result.first == -1 && result.second == -1) {
            cout << "POINT_AT_INFINITY\n";
        } else {
            cout << result.first << " " << result.second << "\n";
        }
    }

    return 0;
}