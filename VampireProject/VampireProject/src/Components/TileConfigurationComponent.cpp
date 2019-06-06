#include "TileConfigurationComponent.hpp"

TileConfigurationComponent::TileConfigurationComponent(TileConfiguration tileConfiguration)
    : mTileConfiguration(tileConfiguration) {

}

TileConfigurationComponent::~TileConfigurationComponent() {

}

void TileConfigurationComponent::FixedUpdateImplementation() {};
void TileConfigurationComponent::VarUpdateImplementation() {};
void TileConfigurationComponent::RenderImplementation() {};

void TileConfigurationComponent::SetTileConfiguration(TileConfiguration tileConfiguration) {
    mTileConfiguration = tileConfiguration;
}

void TileConfigurationComponent::SetType(unsigned char type) {
    mTileConfiguration.mType = type;
}

void TileConfigurationComponent::SetDirection(unsigned char dir) {
    mTileConfiguration.mDir = dir;
}

const TileConfiguration& TileConfigurationComponent::GetTileConfiguration() {
    return mTileConfiguration;
}

unsigned char TileConfigurationComponent::GetType() {
    return mTileConfiguration.mType;
}

unsigned char TileConfigurationComponent::GetDirection() {
    return mTileConfiguration.mDir;
}
