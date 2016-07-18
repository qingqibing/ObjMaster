//
// Created by rthier on 2016.04.11..
//

#include "FacePoint.h"
#include <cstring>    /* strtok_r */
#include <cstdlib>     /* atoi */

namespace ObjMaster {
    bool FacePoint::isParsable(const char *fields) {
        // Basic check (for speed): Not an empty string and the first character is a number...
        if((fields != nullptr) && (fields[0] != 0) && (fields[0] >= '0') && (fields[0] <= '9')) {
            // TODO: still not a full-blown check, but at least do most of the things...
            int delimCount = 0;
            for(int i = 0; (fields[i] != 0) && (i < FACEPOINT_MAXLEN); ++i) {
                if(fields[i] == FACEPOINT_DELIMITER[0]) {
                    ++delimCount;
                }
            }
            if(delimCount == 2) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }


    // No-arg construction
    FacePoint::FacePoint() : vIndex(0), vtIndex(0), vnIndex(0) { }

    // Variant that keeps the original string as it is. Has overhead because of copies.
    FacePoint::FacePoint(const char *fields) {
        if (isParsable(fields)) {
            // The strtok_r changes the string so we need to duplicate it
            char *copy = strdup(fields);
            constructorHelper(copy);
            free(copy);
        }
    }

    // This variant modifies the provided 'string' but is it faster as it do this without the copy
    FacePoint::FacePoint(char *fields) {
        if (isParsable(fields)) {
            constructorHelper(fields);
        }
    }

    // Constructor variant where you can decide if you want to avoid unnecessary "isParsable"
    // Useful when you are sure about the data or did call the check earlier manually
    // so that this way you can avoid unnecessary duplicated checks
    FacePoint::FacePoint(const char *fields, bool forceParser) {
        if (forceParser || isParsable(fields)) {
            // The strtok_r changes the string so we need to duplicate it
            char *copy = strdup(fields);
            constructorHelper(copy);
            free(copy);
        }
    }

    // Constructor variant where you can decide if you want to avoid unnecessary "isParsable"
    // Useful when you are sure about the data or did call the check earlier manually
    // so that this way you can avoid unnecessary duplicated checks
    FacePoint::FacePoint(char *fields, bool forceParser) {
        if (forceParser || isParsable(fields)) {
            constructorHelper(fields);
        }
    }

    // Common parts of the constructors
    void FacePoint::constructorHelper(char* fields) {
        char *savePtr;
        // Fill-in the indices
        char* vIndexStr = strtok_r(fields, FACEPOINT_DELIMITER, &savePtr);
        vIndex = atoi(vIndexStr) - 1;
        char* vtIndexStr = strtok_r(nullptr, FACEPOINT_DELIMITER, &savePtr);
        vtIndex = atoi(vtIndexStr) - 1;
        char* vnIndexStr = strtok_r(nullptr, FACEPOINT_DELIMITER, &savePtr);
        vnIndex = atoi(vnIndexStr) - 1;
    }
}
