#ifndef FIGURES
#define FIGURES

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    T_CIRCLE,
    T_RECTANGLE,
    T_POLYGON,
    T_LINE,
    T_TEXT
} Type_figure;

typedef struct {
    int F_FONTSIZE;
    int F_VISIBLE;
    int F_FILL_COLOR;
    int F_EDGE_COLOR;
    int F_THICKNESS;
} OPTIONS_FLAGS;

struct Options{
    OPTIONS_FLAGS flags;
    char* couleur_tour;
    char* couleur_remplissage;
    int epaisseur;
    char* visibility;
    int fontsize;
};
typedef struct Options Options;

struct Figure{
    char* nom;
    Type_figure type;
    int centre[2];
    int radius;
    Options options;
    int coord1[2];
    int coord2[2];
    int dimensions[2];
    char* texte;
    int is_selected;
};
typedef struct Figure Figure;


struct Image{
    Figure** figures;
    int nb_figures;
};
typedef struct Image Image;

void Init_image(Image* image);

Figure* Create_circle(char* nom, char* centre, int radius);

Figure* Create_line(char* nom, char* coord1,char* coord2);

Figure* Create_rectangle(char* nom,char* coords,char* dimensions);

Figure* Create_text(char* nom,char* texte,char* coords);

void Add_figure(Image* image,Figure* figure);

void Dump_figures(Image image);

void Dump_figures_file(Image image, char* file);

void Delete_figure(Image* image,char* figure);

void Rename_figure(Image* image,char* old_name,char* new_name);

Options* Default_options();

Options* Set_couleur_tour(Options* opt,char* couleur);

Options* Set_epaisseur(Options* opt, int epaisseur);

Options* Set_couleur_remplissage(Options* opt, char* couleur);

Options* Set_visibility(Options* opt, char* visibility);

Options* Set_fontsize(Options* opt, int fontsize);

void Set_options(Image* image,char* figure,Options* options);

void Set_selected(Image* image,char* nom,int is_selected);

void Set_selected_all(Image* image, int is_selected);

void Move(Image* image,char* mouvement);

#endif