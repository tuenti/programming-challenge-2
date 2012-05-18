/* 
    *** Challenge 4: 20 fast 20 furious ***
    
    Compile with:
    g++ -o t4 -O3 t4.cpp
*/

#include <iostream>
#include <fstream>
#include <vector>

/* Class used for storing the information about a race already done.
   This allow us to cache the values and reuse them later when we found
   that the same group want to ride
*/
class Precomputed {
public:
    Precomputed() : valid(false) {}

    bool valid;                     // Indicates if the rest of the information is valid or is not cached yet
    size_t liters;
    size_t next_group_to_ride;
};


int main(void) {
    size_t test_cases;
    std::cin >> test_cases;

    std::vector<size_t> groups;
    std::vector<Precomputed> precomputed;
 
    for(size_t i = 0; i < test_cases; i++) {               
        size_t R, k, G;
        size_t current_group = 0;
        size_t liters_spent = 0;
    
        std::cin >> R;
        std::cin >> k;
        std::cin >> G;

        groups.resize(G);

        // Reset the cache and set all to invalid
        precomputed.clear();
        precomputed.resize(G);

        // Read the number of people for each group
        for(size_t j = 0; j < G; j++) {
            size_t number_of_people;

            std::cin >> number_of_people;

            groups[j] = number_of_people;

        }

        // If we find a group bigger than k, we should stop
        bool no_more_races = false;

        for(size_t current_race = 0; current_race < R && !no_more_races; current_race++) {
            size_t free_karts = k;
            size_t initial_group = current_group;

            if (precomputed[current_group].valid) {
                liters_spent += precomputed[current_group].liters;
                current_group = precomputed[current_group].next_group_to_ride;
             }
            else {
                size_t liters_in_this_race = 0;

                while (free_karts > 0) {
                    // Check if a group is bigger than our maximum number of karts
                    if (groups[current_group] > k) {
                        no_more_races = true;
                        break;
                    }

                    if (groups[current_group] > free_karts)
                        break;
                
                    free_karts -= groups[current_group];
                    liters_in_this_race += groups[current_group];
                    current_group = ++current_group % groups.size();

                    // The same group can't ride twice in the same race even having more free_karts
                    if (current_group == initial_group)
                        break;
                }

                precomputed[initial_group].valid = true;
                precomputed[initial_group].liters = liters_in_this_race;
                precomputed[initial_group].next_group_to_ride = current_group;

                liters_spent += liters_in_this_race;
            }                    
        }

        std::cout << liters_spent << std::endl;
    }
}
