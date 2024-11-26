//
// Created by Lesleis Nagy on 25/11/2024.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>
#include <random>

#include "trees/recursive_octree.hpp" // Replace with the path to your Octree header file

TEST_CASE("Octree: Basic Insertion and Query", "[Octree]") {

  AxisAlignedBoundingBox<double> boundary{0.0, 100.0, 0.0, 100.0, 0.0, 100.0};
  RecursiveOctree<double> octree(boundary, 4, 5);

  SECTION("Insert points within boundary") {
    REQUIRE(octree.insert({10.0, 20.0, 30.0}));
    REQUIRE(octree.insert({40.0, 50.0, 60.0}));
    REQUIRE(octree.insert({70.0, 80.0, 90.0}));

// Query a region that includes all inserted points
    AxisAlignedBoundingBox<double>
        queryRegion{0.0, 100.0, 0.0, 100.0, 0.0, 100.0};
    auto result = octree.query(queryRegion);

    REQUIRE(result.size() == 3);
  }

  SECTION("Insert point outside boundary") {
    REQUIRE_FALSE(octree.insert({150.0, 150.0, 150.0}));
  }

  SECTION("Query a region with no points") {
    AxisAlignedBoundingBox<double>
        queryRegion{90.0, 100.0, 90.0, 100.0, 90.0, 100.0};
    auto result = octree.query(queryRegion);

    REQUIRE(result.empty());
  }
}

TEST_CASE("Octree: Subdivision and Redistribution", "[Octree]") {
  AxisAlignedBoundingBox<double> boundary{0.0, 100.0, 0.0, 100.0, 0.0, 100.0};
  RecursiveOctree<double>
      octree(boundary, 2, 3); // Low maxObjects to force subdivision

  SECTION("Subdivision on exceeding capacity") {
    REQUIRE(octree.insert({10.0, 20.0, 30.0}));
    REQUIRE(octree.insert({40.0, 50.0, 60.0}));
    REQUIRE(octree.insert({70.0, 80.0, 90.0})); // Should trigger subdivision

// Query should still retrieve all points
    AxisAlignedBoundingBox<double>
        queryRegion{0.0, 100.0, 0.0, 100.0, 0.0, 100.0};
    auto result = octree.query(queryRegion);

    REQUIRE(result.size() == 3);
  }
}

TEST_CASE("Octree: Boundary Overlap and Edge Cases", "[Octree]") {

  AxisAlignedBoundingBox<double> boundary{0.0, 100.0, 0.0, 100.0, 0.0, 100.0};
  RecursiveOctree<double> octree(boundary, 4, 5);

  SECTION("Point on boundary edge") {
    REQUIRE(octree.insert({0.0, 0.0, 0.0}));
    REQUIRE(octree.insert({100.0, 100.0, 100.0}));

    AxisAlignedBoundingBox<double> queryRegion{0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    auto result = octree.query(queryRegion);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].x() == Approx(0.0));
    REQUIRE(result[0].y() == Approx(0.0));
    REQUIRE(result[0].z() == Approx(0.0));
  }

  SECTION("Query overlapping boundaries") {
    octree.insert({10.0, 10.0, 10.0});
    octree.insert({50.0, 50.0, 50.0});
    octree.insert({90.0, 90.0, 90.0});

    AxisAlignedBoundingBox<double>
        queryRegion{45.0, 55.0, 45.0, 55.0, 45.0, 55.0};
    auto result = octree.query(queryRegion);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].x() == Approx(50.0));
    REQUIRE(result[0].y() == Approx(50.0));
    REQUIRE(result[0].z() == Approx(50.0));
  }

}

TEST_CASE("Octree: Large Data Insertion", "[Octree]") {

  AxisAlignedBoundingBox<double>
      boundary{0.0, 1000.0, 0.0, 1000.0, 0.0, 1000.0};
  RecursiveOctree<double> octree(boundary, 10, 10);

  SECTION("Insert a large number of points") {
    for (int i = 0; i < 1000; ++i) {
      REQUIRE(octree.insert({static_cast<double>(i),
                             static_cast<double>(i),
                             static_cast<double>(i)}));
    }

    AxisAlignedBoundingBox<double>
        queryRegion{0.0, 1000.0, 0.0, 1000.0, 0.0, 1000.0};
    auto result = octree.query(queryRegion);

    REQUIRE(result.size() == 1000);
  }

}

TEST_CASE("Octree: Output operator", "[Octree]") {

  const int num_points = 10000; // Number of points to sample
  const double min_coord = 0.0; // Minimum coordinate value
  const double max_coord = 100.0; // Maximum coordinate value

  // Define the bounding box for the Octree
  AxisAlignedBoundingBox<double> boundary
      {min_coord, max_coord, min_coord, max_coord, min_coord, max_coord};

  // Create the Octree with a maximum of 4 objects per node and a maximum depth of 5
  RecursiveOctree<double> octree(boundary, 4, 5);

  // Set up a random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(min_coord, max_coord);

  // Generate and insert random points
  for (int i = 0; i < num_points; ++i) {
    double x = dist(gen);
    double y = dist(gen);
    double z = dist(gen);

    octree.insert({x, y, z});
  }

  // Output the DOT graph
  std::ofstream file("/Users/lnagy2/Projects/libfabbri/octree.dot");
  file << octree;
  file.close();

}
