#ifndef WORLD_H 
#define WORLD_H 

#include <stdio.h>
#include <random>
#include <vector>

enum class EpithelialState;

class EpithelialCell;
class ImmuneCell;
class Window;

typedef struct {
    int healthy;
    int s_infected;
    int d_infected;
    int c_infected;
    int dead;
    int immune;
} counts_t;

class World {
public:
    std::vector<counts_t> prev_counts;
    std::vector<counts_t> counts;
    int n_cells_in_section;
    int timestep;
    int base_recruitment_immune_cells;
    double recruitment_probability;
    EpithelialCell*** epithelial_cells; 
    std::vector<ImmuneCell> immune_cells;
    std::vector<ImmuneCell> new_mature_immune_cells;

    World(FILE* out_fp, FILE* section_fp);
    ~World();

    void Step(FILE* out_fp, FILE* section_fp);

    // immune cell recognition event
    void MatureImmuneCellRecognitionEvent(int x, int y);

    // print information about a current timestep
    void PrintInfo(FILE* fp);

private:
    // update 
    void UpdateEpithelialCells();
    void UpdateImmuneCells();

    void PrintTimeStepToFile(FILE* out_fp, FILE* section_fp);

    void AddExtDip();

    void AddNewImmuneCellFromRecognition(int x, int y);

    std::vector<int> GetPatchSizes(EpithelialState patch_state);

    // graphics
    void ClearAndDrawToScreen(Window& window);

    std::uniform_int_distribution<int> x_distribution;
    int RandomX();
    std::uniform_int_distribution<int> y_distribution;
    int RandomY();

    std::uniform_int_distribution<int> epithelial_age_distribution;
    int RandomEpithelialAge();
    std::uniform_int_distribution<int> immune_age_distribution;
    int RandomImmuneAge();
    std::uniform_int_distribution<int> division_time_distribution;
    int RandomDivisionTime();

    // PRINTING
    // print the patch sizes of a type of cell
    void PrintPatchSizes(FILE* fp, EpithelialState patch_state);
    
    // average number of healthy epithelial cell neighbours that a dead epithelial cell
    // has
    void PrintProportionHealthyOfDeadNeighbours(FILE* fp);
};

#endif
