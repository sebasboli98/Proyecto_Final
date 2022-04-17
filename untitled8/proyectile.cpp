#include "proyectile.h"

proyectile::proyectile(float ax, float ay, std::string texture, QGraphicsItem *parent)
{

}

proyectile::proyectile(float px, float py, proyectile *Cast){
    setPos(px, py);
    // Other attributes
}
