#include "scene_component.h"

#include "../core/actor.h"


namespace hge
{
  void HGE_SceneComponent::SetRelativeTransform(HGE_Transform _transform)
  {
    transform_ = _transform;
    LocationModified(transform_.location_);
    RotationModified(transform_.rotation_);
    ScaleModified(transform_.scale_);
  }
  void HGE_SceneComponent::SetRelativeLocation(HGE_Vec3 _location)
  {
    transform_.location_ = _location;
    LocationModified(_location);
  }
  void HGE_SceneComponent::SetRelativeRotation(HGE_Vec3 _rotation)
  {
    transform_.rotation_ = _rotation;
    RotationModified(_rotation);
  }
  void HGE_SceneComponent::SetRelativeScale(HGE_Vec3 _scale)
  {
    transform_.scale_ = _scale;
    ScaleModified(_scale);
  }


  HGE_Transform HGE_SceneComponent::GetRelativeTransform()
  {
    return transform_;
  }
  HGE_Transform HGE_SceneComponent::GetAbsoluteTransform()
  {
    return transform_ * parent_->transform_;
  }

  HGE_Vec3 HGE_SceneComponent::GetRelativeLocation()
  {
    return transform_.location_;
  }
  HGE_Vec3 HGE_SceneComponent::GetAbsoluteLocation()
  {
    return transform_.location_ + parent_->transform_.location_;
  }

  HGE_Vec3 HGE_SceneComponent::GetRelativeRotation()
  {
    return transform_.rotation_;
  }
  HGE_Vec3 HGE_SceneComponent::GetAbsoluteRotation()
  {
    return transform_.rotation_ + parent_->transform_.rotation_;
  }

  HGE_Vec3 HGE_SceneComponent::GetRelativeScale()
  {
    return transform_.scale_;
  }
  HGE_Vec3 HGE_SceneComponent::GetAbsoluteScale()
  {
    return transform_.scale_ * parent_->transform_.scale_;
  }
}