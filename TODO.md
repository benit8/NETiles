# NETiles

## Objectifs
Documentation (UML)
Rework common project parts
GUI

### Editor
Rewrite editor with new core/
Rewrite level file structure :
- Binary format
- Header magic 'NETwld__'
	- __: format version
- Level name, type (?), size, tiles
- Tile textures used

Sub rooms (e.g. houses)

### Client
Mise en cache des map et tileset