TTF_Font *gFont, *gFontOutline;

bool loadMedia() {
}

void loadFont(int size) {
  gFont= TTF_OpenFont("resources/fonts/font1.ttf", size);
  gFontOutline = TTF_OpenFont("resources/fonts/font1.ttf", size);
}
