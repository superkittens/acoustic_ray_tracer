//
//  RTFileWriter_Tests.cpp
//  acoustic_raytracer
//
//  Created by Allen Lee on 2022-02-10.
//

#define CATCH_CONFIG_MAIN

#include <stdio.h>
#include <catch2/catch.hpp>
#include <vector>
#include <array>
#include <fstream>

#include "RTFileWriter.hpp"



TEST_CASE("Write IR to File")
{
    std::vector<float> ir{0.0, 1.0, 2.0, 3.0};
    RTFileWriter fileWriter;
    
    SECTION("Blocking")
    {
        std::string path = "/Users/superkittens/Desktop/ir_test_blocking.txt";
        fileWriter.writeIRToFile(ir, path, true);
        
        std::ifstream inputStream(path, std::ios_base::in);
        REQUIRE(inputStream.is_open() == true);
        
        std::vector<std::array<char, 16>> v;
        
        for (std::array<char, 16> a; inputStream.getline(&a[0], 16, '\n'); )
            v.push_back(a);
        
        REQUIRE(v.size() == ir.size());
        
        for (auto i = 0; i < v.size(); ++i)
            REQUIRE(atof(v[i].data()) == ir[i]);
        
        REQUIRE(fileWriter.getWritingProgress().first == 1.0);
    }
    
    SECTION("Asynchronous")
    {
        std::string path ="/Users/superkittens/Desktop/ir_test_async.txt";
        fileWriter.writeIRToFile(ir, path, false);
        
        while(fileWriter.isWriting());

        std::ifstream inputStream(path, std::ios_base::in);
        REQUIRE(inputStream.is_open() == true);
        
        std::vector<std::array<char, 16>> v;
        
        for (std::array<char, 16> a; inputStream.getline(&a[0], 16, '\n'); )
            v.push_back(a);
        
        REQUIRE(v.size() == ir.size());
        
        for (auto i = 0; i < v.size(); ++i)
            REQUIRE(atof(v[i].data()) == ir[i]);
    }
    
    //  Setup for invalid inputs tests
    std::string path = "/Users/superkittens/Desktop/invalid.txt";
    
    SECTION("Invalid Inputs", "[Invalid IR]")
    {
        std::vector<float> invalidIR;
        REQUIRE(fileWriter.writeIRToFile(invalidIR, path, true) == false);
    }
    
    SECTION("Invalid Inputs", "[Invalid Path]")
    {
        REQUIRE(fileWriter.writeIRToFile(ir, "", true) == false);
    }
}
