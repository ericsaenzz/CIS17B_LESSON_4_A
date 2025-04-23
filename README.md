# CIS17B_LESSON_4_A
ERIC CHANG

Assignment 4: Storage Management System using Ordered and Unordered Collections

# Project Description
You are the CTO for "Congo", the second largest rainforest-themed Online retailer in the world.  You are developing a system for your smart warehouse that manages thousands of stored items. Each item has a unique ID, a description, and a storage location (like “Aisle 4, Shelf 2”).

Your system must support:

Fast item lookup by ID (use std::unordered_map)

Listing items in alphabetical order of their description (use std::map)

Handling errors such as attempting to retrieve an item that doesn’t exist

You’ll also use smart pointers for memory safety and write test functions to validate edge cases like duplicate entries or invalid removals.