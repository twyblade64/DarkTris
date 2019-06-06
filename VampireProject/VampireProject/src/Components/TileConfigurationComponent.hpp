#ifndef HEX_TILE_CONFIGURATION_COMPONENT_H_
#define HEX_TILE_CONFIGURATION_COMPONENT_H_

#include "../Core/Component.hpp"
#include "TileConfiguration.hpp"

class TileConfigurationComponent: public Component<TileConfigurationComponent> {
public:
    TileConfigurationComponent(TileConfiguration tileConfiguration);
    ~TileConfigurationComponent() override;
public:
    void FixedUpdateImplementation();
    void VarUpdateImplementation();
    void RenderImplementation();
public:
    void SetTileConfiguration(TileConfiguration tileConfiguration);
    void SetType(unsigned char type);
    void SetDirection(unsigned char dir);
    const TileConfiguration& GetTileConfiguration();
    unsigned char GetType();
    unsigned char GetDirection();
private:
    TileConfiguration mTileConfiguration;
};

#endif // HEX_TILE_CONFIGURATION_COMPONENT_H_
