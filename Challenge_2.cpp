/* Jake Busler
 * 9/15/2026.
 * MCSCI-272 (5238)
 * Challenge 2: Dynamic Grade Analysis with std::vector
 */

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <limits>
#include <iomanip>

// Flush stream state and clear input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Display menu and enforce input validation (1-6)
int menu() {
    int choice = 0;
    while (true) {
        std::cout << "\n========================================\n";
        std::cout << "        Grade Analysis System           \n";
        std::cout << "========================================\n";
        std::cout << "1. Add a Grade\n";
        std::cout << "2. Display All Grades\n";
        std::cout << "3. Calculate Average Grade\n";
        std::cout << "4. Find Highest and Lowest Grade\n";
        std::cout << "5. Count Grades Above Threshold\n";
        std::cout << "6. Quit\n";
        std::cout << "Select an option (1-6): ";

        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 6) {
                return choice;
            }
            std::cout << "[!] Option out of range. Please enter a value between 1 and 6.\n";
        } else {
            std::cout << "[!] Invalid non-numeric input. Please try again.\n";
            clearInputBuffer();
        }
    }
}

// 1. Add Grade
void addGrade(std::vector<double>& grades) {
    double grade = 0.0;
    std::cout << "Enter grade to add (e.g. 85.5): ";
    if (std::cin >> grade) {
        if (grade >= 0.0) {
            grades.push_back(grade);
            std::cout << "Grade " << std::fixed << std::setprecision(2)
                      << grade << " added successfully.\n";
        } else {
            std::cout << "[!] Grade cannot be negative.\n";
        }
    } else {
        std::cout << "[!] Invalid numerical value. Grade not added.\n";
        clearInputBuffer();
    }
}

// 2. Display All Grades
void displayAllGrades(const std::vector<double>& grades) {
    if (grades.empty()) {
        std::cout << "[!] No grades recorded yet.\n";
        return;
    }

    std::cout << "\n--- Current Grades (" << grades.size() << " total) ---\n";
    for (size_t i = 0; i < grades.size(); ++i) {
        std::cout << "Grade #" << (i + 1) << ": "
                  << std::fixed << std::setprecision(2) << grades[i] << "\n";
    }
}

// 3. Calculate Average Grade (Guarded against division by zero)
void calculateAverageGrade(const std::vector<double>& grades) {
    if (grades.empty()) {
        std::cout << "[!] Cannot calculate average: vector is empty.\n";
        return;
    }

    double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
    double avg = sum / static_cast<double>(grades.size());

    std::cout << "Average Grade: " << std::fixed << std::setprecision(2) << avg << "\n";
}

// 4. Find Highest and Lowest Grade
void findHighestAndLowest(const std::vector<double>& grades) {
    if (grades.empty()) {
        std::cout << "[!] Cannot find min/max: vector is empty.\n";
        return;
    }

    auto minIt = std::min_element(grades.begin(), grades.end());
    auto maxIt = std::max_element(grades.begin(), grades.end());

    std::cout << "Lowest Grade : " << std::fixed << std::setprecision(2) << *minIt << "\n";
    std::cout << "Highest Grade: " << std::fixed << std::setprecision(2) << *maxIt << "\n";
}

// 5. Count Grades Above Threshold
void countGradesAboveThreshold(const std::vector<double>& grades) {
    if (grades.empty()) {
        std::cout << "[!] No grades stored. Add grades before evaluating thresholds.\n";
        return;
    }

    double threshold = 0.0;
    std::cout << "Enter score threshold: ";
    if (std::cin >> threshold) {
        long long count = std::count_if(grades.begin(), grades.end(), [threshold](double g) {
            return g > threshold;
        });

        std::cout << "Grades strictly greater than " << std::fixed << std::setprecision(2)
                  << threshold << ": " << count << " out of " << grades.size() << "\n";
    } else {
        std::cout << "[!] Invalid numerical value for threshold.\n";
        clearInputBuffer();
    }
}

int main() {
    // Vector declared inside main() as specified
    std::vector<double> grades;
    int choice = 0;

    do {
        choice = menu();

        switch (choice) {
            case 1:
                addGrade(grades);
                break;
            case 2:
                displayAllGrades(grades);
                break;
            case 3:
                calculateAverageGrade(grades);
                break;
            case 4:
                findHighestAndLowest(grades);
                break;
            case 5:
                countGradesAboveThreshold(grades);
                break;
            case 6:
                std::cout << "Exiting Grade Analysis System. Goodbye!\n";
                break;
            default:
                std::cout << "[!] Invalid state encountered.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
