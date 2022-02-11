//
//  RTFileWriter.cpp
//  acoustic_raytracer
//
//  Created by Allen Lee on 2022-02-10.
//

#include "RTFileWriter.hpp"

bool RTFileWriter::isWriting() const
{
    std::lock_guard<std::mutex> guard(_lock);
    return _writeInProgress;
}

bool RTFileWriter::writeIRToFile(const std::vector<float>& ir, const std::string& path, bool blocking)
{
    if (ir.empty() || path == "")
        return false;
    
    if (isWriting())
        return false;
    
    reset();
    
    _writeInProgress = true;
    
    if (blocking)
        return writeIRHelper(ir, path);
    
    else
    {
        std::thread irWriteThread([&]() { writeIRHelper(ir, path); });
        irWriteThread.detach();
    }
    
    return true;
}

std::pair<float, bool> RTFileWriter::getWritingProgress() const
{
    std::lock_guard<std::mutex> guard(_lock);
    return std::make_pair(_progress, _exceptionOccured);
}

bool RTFileWriter::writeIRHelper(const std::vector<float>& ir, const std::string& path)
{
    bool success = true;
    
    try
    {
        std::ofstream outputFile(path, std::ios_base::out);
        float index = 0;
        const float irSize = static_cast<float>(ir.size());
        
        for (const auto& value : ir)
        {
            std::lock_guard<std::mutex> guard(_lock);
            
            outputFile << std::to_string(value) << "\n";
            
            index += 1.0;
            _progress = index / irSize;
        }
        
    } catch (const std::ios_base::failure& fail)
    {
        _exceptionOccured = true;
        std::cout << fail.what() << "\n";
        success = false;
    }
    
    std::lock_guard<std::mutex> guard(_lock);
    _writeInProgress = false;
    
    return success;
}

void RTFileWriter::reset()
{
    _writeInProgress = false;
    _exceptionOccured = false;
    _progress = 0.0;
}

