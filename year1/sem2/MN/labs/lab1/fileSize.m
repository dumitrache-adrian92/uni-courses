function [x] = fileSize(filename)
    s = dir(filename);
    x = s.bytes;