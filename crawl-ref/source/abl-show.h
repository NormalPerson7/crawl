/*
 *  File:       abl-show.h
 *  Summary:    Functions related to special abilities.
 *  Written by: Linley Henzell
 */


#ifndef ABLSHOW_H
#define ABLSHOW_H

#include "enum.h"

#include <string>
#include <vector>

struct generic_cost
{
    int base, add, rolls;

    generic_cost(int num)
        : base(num), add(num == 0 ? 0 : (num + 1) / 2 + 1), rolls(1)
    {
    }
    generic_cost(int num, int _add, int _rolls = 1)
        : base(num), add(_add), rolls(_rolls)
    {
    }
    static generic_cost fixed(int fixed)
    {
        return generic_cost(fixed, 0, 1);
    }
    static generic_cost range(int low, int high, int _rolls = 1)
    {
        return generic_cost(low, high - low + 1, _rolls);
    }

    int cost() const;

    operator bool () const { return base > 0 || add > 0; }
};

struct scaling_cost
{
    int value;

    scaling_cost(int permille) : value(permille) {}

    static scaling_cost fixed(int fixed)
    {
        return scaling_cost(-fixed);
    }

    int cost(int max) const;

    operator bool () const { return value != 0; }
};

// Structure for representing an ability:
struct ability_def
{
    ability_type        ability;
    const char *        name;
    unsigned int        mp_cost;        // magic cost of ability
    scaling_cost        hp_cost;        // hit point cost of ability
    unsigned int        food_cost;      // + rand2avg( food_cost, 2 )
    generic_cost        piety_cost;     // + random2( (piety_cost + 1) / 2 + 1 )
    unsigned int        flags;          // used for additonal cost notices
    unsigned int        xp_cost;        // hit point cost of ability
};

struct talent
{
    ability_type which;
    int hotkey;
    int fail;
    bool is_invocation;
};

const ability_def& get_ability_def(ability_type);

const std::string make_cost_description(ability_type ability);
const char* ability_name(ability_type ability);
std::vector<const char*> get_ability_names();
int choose_ability_menu(const std::vector<talent>& talents);

bool activate_ability();
std::vector<talent> your_talents(bool check_confused);
bool string_matches_ability_name(const std::string& key);
std::string print_abilities(void);

void set_god_ability_slots(void);


#endif
