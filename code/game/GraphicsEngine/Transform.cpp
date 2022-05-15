#include <iostream>
#include "Transform.h"

namespace Graphics {

    Transform::Transform(glm::vec3 startRotation, glm::vec3 startTranslation, glm::vec3 startScale) {
        translation = startTranslation;
        scale = startScale;
        SetRotation(startRotation);
        rotationQuaternion = glm::quat(glm::radians(glm::vec3(1,1,1)));
    }

    void Transform::SetRotation(glm::vec3 targetRotation) {
        rotation = targetRotation;
        recalculateModel();
    }

    void Transform::AddRotation(glm::vec3 additiveRotation) {
        /*glm::vec3 newRotation = GetRotation() + additiveRotation;

        SetRotation(newRotation);*/
        rotationQuaternion *= glm::quat(glm::radians(additiveRotation));
    }

    glm::vec3 Transform::GetRotation() {
        return rotation;
    }

    void Transform::SetTranslation(glm::vec3 targetTranslation) {
        translation = targetTranslation;
        recalculateModel();
    }

    void Transform::AddTranslation(glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = GetTranslation() + additiveTranslation;
        SetTranslation(newTranslation);
    }

    glm::vec3 Transform::GetTranslation() {
        return translation;
    }

    void Transform::SetScale(glm::vec3 targetScale) {
        scale = targetScale;
        recalculateModel();
    }

    void Transform::AddScale(glm::vec3 additiveScale) {
        glm::vec3 newScale = GetScale() + additiveScale;
        SetScale(newScale);
    }

    glm::vec3 Transform::GetScale() {
        return scale;
    }

    glm::mat4* Transform::GetModelMatrix() {
        return &modelMatrix;
    }

    glm::mat4 Transform::GetInverseModelMatrix() {
        return inverseModelMatrix;
    }

    void Transform::recalculateModel() {
        glm::mat4 rotateModel = glm::mat4 (1.0f);
        float rotationAngle;
        //test = glm::translate(test, translation);
        float fx = rotation.x, fy = rotation.y, fz = rotation.z;
        //if(rotation.y > 90) rotation.y = 90;

        /*if(rotation.x >= 1){
            rotationAngle = rotation.x;
            rotateModel = *//*glm::rotate(test, rotation.x, rotationAxis);*//*glm::mat4_cast(glm::angleAxis(rotationAngle, glm::normalize(rotation)))*//*glm::quat(rotation)*//*;
        *//*glm::vec3 rotationAxis(1, rotation.y/rotation.x, rotation.z/rotation.x);
        rotationAxis = glm::normalize(rotationAxis);
        rotateModel = glm::rotate(test, rotation.x, rotationAxis);glm::mat4_cast(glm::angleAxis(rotation.x, rotationAxis))glm::quat(rotation);*//*
        } else if(rotation.y >= 1){
            rotationAngle = rotation.y;
            rotateModel = *//*glm::rotate(test, rotation.x, rotationAxis);*//*glm::mat4_cast(glm::angleAxis(rotationAngle, glm::normalize(rotation)))*//*glm::quat(rotation)*//*;
            *//*glm::vec3 rotationAxis(rotation.x/rotation.y, 1, rotation.z/rotation.y);
            rotationAxis = glm::normalize(rotationAxis);
            rotateModel = glm::rotate(test, rotation.x, rotationAxis);glm::mat4_cast(glm::angleAxis(rotation.y, rotationAxis))glm::quat(rotation);*//*
        } else if(rotation.z >= 1){
            rotationAngle = rotation.z;
            rotateModel = *//*glm::rotate(test, rotation.x, rotationAxis);*//*glm::mat4_cast(glm::angleAxis(rotationAngle, glm::normalize(rotation)))*//*glm::quat(rotation)*//*;
            *//*glm::vec3 rotationAxis(rotation.x/rotation.z, rotation.y/rotation.z, 1);
            rotationAxis = glm::normalize(rotationAxis);
            rotateModel = glm::rotate(test, rotation.x, rotationAxis);glm::mat4_cast(glm::angleAxis(rotation.z, rotationAxis))glm::quat(rotation);*//*
        }*/
        /*test = glm::scale(test, scale);
        modelMatrix = test;*/
        //auto rotationAxis = noglm::vec3(1.0f, rotation.y/rotation.x, rotation.z/rotation.x);
        // Assuming the angles are in radians.
        /*double c1 = cos(rotation.x/2);
        double s1 = sin(rotation.x/2);
        double c2 = cos(rotation.y/2);
        double s2 = sin(rotation.y/2);
        double c3 = cos(rotation.z/2);
        double s3 = sin(rotation.z/2);
        double c1c2 = c1*c2;
        double s1s2 = s1*s2;
        float w =c1c2*c3 - s1s2*s3;
        float x =c1c2*s3 + s1s2*c3;
        float y =s1*c2*c3 + c1*s2*s3;
        float z =c1*s2*c3 - s1*c2*s3;
        angle = 2 * acos(w);
        double norm = x*x+y*y+z*z;
        if (norm < 0.001) { // when all euler angles are zero angle =0 so
            // we can set axis to anything to avoid divide by zero
            x=1;
            y=z=0;
        } else {
            norm = sqrt(norm);
            x /= norm;
            y /= norm;
            z /= norm;
        }*/
        //std::cout<<"Prev Angles: "<<rotation.x<<","<<rotation.y<<","<<rotation.z<<std::endl;
        glm::mat4 translateModel = glm::translate(glm::mat4(1.0f), translation);
        //glm::mat4 rotateModel = glm::mat4_cast(glm::angleAxis(rotation.x, glm::vec3(0.5,0.5,0))/*glm::quat(rotation)*/);
        glm::mat4 scaleModel = glm::scale(glm::mat4(1.0f), scale);
        auto rotationQuat = glm::quat(rotation);
        rotateModel = glm::mat4_cast(rotationQuaternion);
        auto eulerTest = glm::eulerAngles(rotationQuaternion);
        //std::cout<<eulerTest.x<<","<<eulerTest.y<<","<<eulerTest.z<<std::endl;
        modelMatrix = translateModel * rotateModel * scaleModel;
        inverseModelMatrix = scaleModel * rotateModel * translateModel;
    }
}