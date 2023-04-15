#include "figures.h"
#include <string.h>

int* str_to_coord(char* str_coord);
int* str_to_dimensions(char* str_coord);
int find_figure(Image image, char* figure);

void Init_image(Image* image){
    image->figures = malloc(0);
    image->nb_figures = 0;
}

Figure* Create_circle(char* nom,char* centre, int radius){
    Figure* figure = malloc(sizeof(Figure));
    figure->nom = nom;
    figure->type = T_CIRCLE;
    int* coord = str_to_coord(centre);
    figure->centre[0] = coord[0];
    figure->centre[1] = coord[1];
    figure->radius = radius;
    figure->options = *Default_options();
    return figure;
}

Figure* Create_line(char* nom, char* coord1,char* coord2){
    Figure* figure = malloc(sizeof(Figure));
    figure->nom = nom;
    figure->type = T_LINE;
    int* coord = str_to_coord(coord1);
    figure->coord1[0] = coord[0];
    figure->coord1[1] = coord[1];
    coord = str_to_coord(coord2);
    figure->coord2[0] = coord[0];
    figure->coord2[1] = coord[1];
    return figure;
}

Figure* Create_rectangle(char* nom,char* coords,char* dimensions){
    Figure* figure = malloc(sizeof(Figure));
    figure->nom = nom;
    figure->type = T_RECTANGLE;
    int* coord = str_to_coord(coords);
    figure->centre[0] = coord[0];
    figure->centre[1] = coord[1];
    int* dimension = str_to_dimensions(dimensions);
    figure->dimensions[0] = dimension[0];
    figure->dimensions[1] = dimension[1];
    return figure;
}

Figure* Create_text(char* nom,char* texte,char* coords){
    Figure* figure = malloc(sizeof(Figure));
    figure->nom = nom;
    figure->type = T_TEXT;
    figure->texte = texte;
    int* coord = str_to_coord(coords);
    figure->centre[0] = coord[0];
    figure->centre[1] = coord[1];
    return figure;
}

Options* Default_options(){
    Options* options = malloc(sizeof(Options));
    options->couleur_tour = "black";
    options->couleur_remplissage = "black";
    options->epaisseur = 1;
    options->fill = 1;
    options->visible = 1;
    return options;
}

int* str_to_coord(char* str_coord){
    int* result = (int*)malloc(2 * sizeof(int)); 
    char* pch;
    pch = strtok(str_coord, "(,)");  
    result[0] = atoi(pch);  
    pch = strtok(NULL, "(,)");
    result[1] = atoi(pch); 
    return result;
}

int* str_to_dimensions(char* str_coord){
    int* result = (int*)malloc(2 * sizeof(int)); 
    char* pch;
    pch = strtok(str_coord, "x");
    result[0] = atoi(pch); 
    pch = strtok(NULL, "x");
    result[1] = atoi(pch); 
    return result;
}

void Add_figure(Image* image,Figure* figure){
    if(find_figure(*image,figure->nom) != -1){
        fprintf(stderr,"Une figure avec ce nom existe deja !\n");
        return;
    }
    image->nb_figures++;
    image->figures = realloc(image->figures,sizeof(Figure)*image->nb_figures);
    image->figures[image->nb_figures-1] = figure;
}

void Dump_figures(Image image){
    printf("DUMP\n");
    printf("nb_figures %d\n",image.nb_figures);
    for(int i=0;i<image.nb_figures;i++){
        switch(image.figures[i]->type){
            case T_CIRCLE:
                fprintf(stdout,"Figure %d CIRCLE : %s centre -> (%d,%d) tour : %s epaisseur : %d fill : %s\n",i,image.figures[i]->nom,image.figures[i]->centre[0],image.figures[i]->centre[1],image.figures[i]->options.couleur_tour,image.figures[i]->options.epaisseur,image.figures[i]->options.couleur_remplissage);
                break;
            case T_LINE:
                fprintf(stdout,"Figure %d LINE : %s coord 1 -> (%d,%d) coord 2 : (%d,%d) \n",i,image.figures[i]->nom,image.figures[i]->coord1[0],image.figures[i]->coord1[1],image.figures[i]->coord1[0],image.figures[i]->coord1[1]);
                break;
            case T_RECTANGLE:
                fprintf(stdout,"Figure %d  RECTANGLE : %s centre -> (%d,%d) width : %d height : %d tour : %s epaisseur : %d fill : %s\n",i,image.figures[i]->nom,image.figures[i]->centre[0],image.figures[i]->centre[1],image.figures[i]->dimensions[0],image.figures[i]->dimensions[1],image.figures[i]->options.couleur_tour,image.figures[i]->options.epaisseur,image.figures[i]->options.couleur_remplissage);
                break;
            case T_TEXT:
                fprintf(stdout,"Figure %d TEXT : %s coord -> (%d,%d) texte : %s \n",i,image.figures[i]->nom,image.figures[i]->coord1[0],image.figures[i]->coord1[1],image.figures[i]->texte);
                break;
        }
       
    }
}

void Dump_figures_file(Image image, char* file){
    printf("DUMP\n");

    FILE* fp = fopen( file, "w" );

    fprintf(fp,"<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"800\" height=\"600\" viewBox=\"0 0 800 600\">");

    for(int i=0;i<image.nb_figures;i++){
        switch(image.figures[i]->type){
            case T_CIRCLE:
                fprintf(fp,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"%s\" stroke-width=\"%d\" fill=\"%s\" />",image.figures[i]->centre[0],image.figures[i]->centre[1],image.figures[i]->radius,image.figures[i]->options.couleur_tour,image.figures[i]->options.epaisseur,image.figures[i]->options.couleur_remplissage);
                break;
            case T_LINE:
                fprintf(fp,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" />",image.figures[i]->coord1[0],image.figures[i]->coord1[1],image.figures[i]->coord2[0],image.figures[i]->coord2[1]);
                break;
            case T_RECTANGLE:
                fprintf(fp,"<rect x=\"%d\" y=\"%d\" height=\"%d\" width=\"%d\" />",image.figures[i]->centre[0],image.figures[i]->centre[1],image.figures[i]->dimensions[0],image.figures[i]->dimensions[1]);
                break;
            case T_TEXT:
                fprintf(fp,"<text x=\"%d\" y=\"%d\" >%s</text>",image.figures[i]->centre[0],image.figures[i]->centre[1],image.figures[i]->texte);
                break;
        }
       
    }

    fprintf(fp,"</svg>");

    fclose(fp);
}

void Delete_figure(Image* image,char* figure){
    int pos_figure = find_figure(*image,figure);
    if(pos_figure != -1){
        free(image->figures[pos_figure]);
        for(int y = pos_figure;y<image->nb_figures-1;y++){
            *(image->figures[y]) = *(image->figures[y+1]);
        }
        image->nb_figures--;
    }
}

void Rename_figure(Image* image,char* old_name,char* new_name){
    int pos_figure = find_figure(*image,old_name);
    if(pos_figure == -1){
        fprintf(stderr,"La figure %s est introuvable\n",old_name);
        return;
    }
    if(find_figure(*image,new_name) != -1){
        fprintf(stderr,"Une figure a déjà le nom %s\n",new_name);
        return;
    }
    image->figures[pos_figure]->nom = new_name;
}

int find_figure(Image image, char* figure){
    for(int i=0;i<image.nb_figures;i++){
        if(strcmp(image.figures[i]->nom,figure) == 0){
            return i;
        }
    }
    return -1;
}

Options* Set_couleur_tour(Options* opt,char* couleur){
    opt->couleur_tour = couleur;
    return opt;
}

Options* Set_epaisseur(Options* opt, int epaisseur){
    opt->epaisseur = epaisseur;
    return opt;
}

Options* Set_couleur_remplissage(Options* opt, char* couleur){
    opt->couleur_remplissage = couleur;
    return opt;
}

Options* Set_fill(Options* opt,int is_filled){
    opt->fill = is_filled;
    return opt;
}

Options* Set_visible(Options* opt, int is_visible){
    opt->visible = is_visible;
    return opt;
}

Options* Set_fontsize(Options* opt, int fontsize){
    opt->fontsize = fontsize;
    return opt;
}

void Set_options(Image* image,char* figure,Options* options){

    int pos_figure = find_figure(*image,figure);
    image->figures[pos_figure]->options = *options;
    Dump_figures(*image);
}

/*
void delete_elem_array(void* tab,int e){
    int size = sizeof(tab) / sizeof(tab[0]);
    for(int i = e;i<size;i++){
        tab[i] = tab[i+1];
    }
    tab = realloc(tab,sizeof(tab[0])*size-1);
}
*/