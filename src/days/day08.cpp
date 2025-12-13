#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

#include "utils/input.hpp"
#include "utils/print.hpp"

namespace day08 {

struct Point {
    int x, y, z;
};

std::vector<Point> getPoints(std::vector<std::string> lines) {
    // Read data into a vector of points:
    std::vector<Point> points;
    for (auto line : lines) {
        auto components = splitString(line, ',');

        Point p;
        p.x = std::stof(components[0]);
        p.y = std::stof(components[1]);
        p.z = std::stof(components[2]);

        points.push_back(p);
    }

    return points;
}

std::vector<long long> calculateDistances(std::vector<Point>& points) {
    int numPoints = points.size();
    
    std::vector<long long> distances(numPoints * numPoints);

    // For each pair of points, calculate the squared distances:
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points.size(); j++) {
            Point& a = points[i];
            Point& b = points[j];

            long long dx, dy, dz;
            dx = a.x - b.x;
            dy = a.y - b.y;
            dz = a.z - b.z;

            distances[i*numPoints + j] = dx*dx + dy*dy + dz*dz;
        }
    }

    return distances;
}

std::vector<size_t> getSortedIndices(std::vector<long long>& distances) {
    // Generate a vector where we will store the sorted indices based on distance.
    // Fill vector with indices:
    std::vector<size_t> sortedIndices(distances.size());
    for (size_t i = 0; i < sortedIndices.size(); i++) {
        sortedIndices[i] = i;
    }

    // Sort the indices:
    std::sort(sortedIndices.begin(), sortedIndices.end(), [&distances](size_t a, size_t b) {return distances[a] < distances[b]; });

    return sortedIndices;
}

std::pair<size_t, size_t> pointIndicesFromDistanceIndex(size_t distanceIndex, size_t numPoints) {
    size_t a, b;
    b = distanceIndex % numPoints;
    a = distanceIndex / numPoints;

    return std::pair<size_t, size_t>(a, b);
}

size_t getRootIndex (std::vector<size_t>& parentIndices, size_t index) {
    if (parentIndices[index] == index) return index;

    return getRootIndex(parentIndices, parentIndices[index]);
}

void part1() {
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day08.txt");
    auto points = getPoints(lines);

    unsigned int numPoints = lines.size();
    auto distances = calculateDistances(points);
    auto sortedIndices = getSortedIndices(distances);

    // Vector storing an index representing a connection. Lower index will always be the parent.
    auto parentIndices = std::vector<size_t>(numPoints);
    for (int i = 0; i < parentIndices.size(); i++) {
        parentIndices[i] = i;
    }

    // For part 1, we only connect the 1000 closest juntion boxes:
    int i = 0, checkedIndices = 0;
    while (checkedIndices < 1000) {
        if (i >= distances.size()) break; // In case there are fewer distances than we want to check

        auto [a, b] = pointIndicesFromDistanceIndex(sortedIndices[i], numPoints);

        if (a <= b) {
            i++;
            continue;
        }

        auto rootA = getRootIndex(parentIndices, a);
        auto rootB = getRootIndex(parentIndices, b);

        // Merge roots. If rootA == rootB they are already in the circuit, and we do nothing
        if (rootA < rootB) {
            parentIndices[rootB] = rootA;
        }
        else if (rootB < rootA) {
            parentIndices[rootA] = rootB;
        }

        checkedIndices++;
        i++;
    }

    // Count how many elements are in each circuit, where the lowest index is the root:
    std::vector<int> connectedJunctions(numPoints); // Auto initialized to 0
    for (size_t i = 0; i < parentIndices.size(); i++) {
        size_t rootIndex = getRootIndex(parentIndices, i);
        connectedJunctions[rootIndex]++;
    }

    // Sort connectedJunctions based on number of junctions:
    std::sort(connectedJunctions.begin(), connectedJunctions.end(), std::greater<>());

    // Calculate the solution:
    long long solution = connectedJunctions[0] * connectedJunctions[1] * connectedJunctions[2];

    std::cout << "Day08, part 1: " << solution << "\n";
}

void part2() {
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day08.txt");
    auto points = getPoints(lines);

    unsigned int numPoints = lines.size();
    auto distances = calculateDistances(points);
    auto sortedIndices = getSortedIndices(distances);

    // Vector storing an index representing a connection. Lower index will always be the parent.
    auto parentIndices = std::vector<size_t>(numPoints);
    for (int i = 0; i < parentIndices.size(); i++) {
        parentIndices[i] = i;
    }

    // Vector to store the number of junction boxes in circuits with the given root as index:
    std::vector<int> junctionsInRoot(numPoints, 1);

    // For part 2, we connect until the whole thing is one giant circuit.
    // This is the case when the root 0 has 1000 elements.
    // We need to store the x coordinates of the last two junction boxes added together.
    long long x1, x2;
    int i = 0;
    while (true) {
        if (i >= distances.size()) break; // In case there are fewer distances than we want to check

        auto [a, b] = pointIndicesFromDistanceIndex(sortedIndices[i], numPoints);

        if (a <= b) {
            i++;
            continue;
        }

        auto rootA = getRootIndex(parentIndices, a);
        auto rootB = getRootIndex(parentIndices, b);

        // Merge roots. If rootA == rootB they are already in the circuit, and we do nothing.
        // We update the number of junction boxes for the given root when we merge.
        if (rootA < rootB) {
            parentIndices[rootB] = rootA;
            junctionsInRoot[rootA] += junctionsInRoot[rootB];
            junctionsInRoot[rootB] = 0;
        }
        else if (rootB < rootA) {
            parentIndices[rootA] = rootB;
            junctionsInRoot[rootB] += junctionsInRoot[rootA];
            junctionsInRoot[rootA] = 0;
        }

        // If root 0 has 1000 elements, we are done:
        if (junctionsInRoot[0] >= numPoints) {
            x1 = points[a].x;
            x2 = points[b].x;
            break;
        }
        
        i++;
    }

    // Calculate the solution:
    long long solution = x1 * x2;

    std::cout << "Day08, part 2: " << solution << "\n";
}

void solve() {
    part1();
    part2();
}

}