//
//  RTFileWriter.hpp
//  acoustic_raytracer
//
//  Created by Allen Lee on 2022-02-10.
//

#ifndef RTFileWriter_hpp
#define RTFileWriter_hpp

#include <stdio.h>
#include <thread>
#include <mutex>
#include <fstream>
#include <vector>
#include <iostream>

class RTFileWriter
{
protected:
    bool _writeInProgress = false;
    bool _exceptionOccured = false;
    float _progress = 0.0;
    mutable std::mutex _lock;
    
    bool writeIRHelper(const std::vector<float>& ir, const std::string& path);
    void reset();
    
public:
    bool isWriting() const;
    bool writeIRToFile(const std::vector<float>& ir, const std::string& path, bool blocking);
    
    //  Get progress (percentage) of file write (first entry in pair)
    //  Also, get any indication of exceptions that may have occured during the writing process (second entry in pair)
    std::pair<float, bool> getWritingProgress() const;
};

#endif /* RTFileWriter_hpp */
