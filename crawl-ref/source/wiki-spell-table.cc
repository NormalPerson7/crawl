

#include "spell-type.h"

struct spell_desc
{
    spell_type id;
    const char  *title;
    spschools_type disciplines;
    spell_flags flags;       // bitfield
    unsigned int level;

    // Usually in the range 0..200 (0 means uncapped).
    // Note that some spells are also capped through zap_type.
    // See spell_power_cap below.
    int power_cap;

    // At power 0, you get min_range. At power power_cap, you get max_range.
    int min_range;
    int max_range;

    // Some spells have a noise at their place of effect, in addition
    // to their casting noise.
    // For zap-based spells, effect_noise is used automatically (if it exists)
    // on hit. For all other spells, it needs to be called manually.
    int effect_noise;

    /// Icon for the spell in e.g. spellbooks, casting menus, etc.
    tileidx_t tile;
};

#include "spl-data.h"
#include "book-data.h"
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include "spl-book.h"
#include "spl-cast.h"
#include "stringutil.h"
#include "database.h"
#include "spl-util.h"

void wiki_table_of_spells();
void table_of_spells();
void table_of_spellbooks();
string spell_table_entry(spell_type spell);
string spell_books(spell_type spell);
string spell_schools(spell_type spell);
string spell_flag_list(spell_type spell);
const char * book_name(book_type book);
const char * flag_name(spflag flag);
string spellbook_table_entry(int book);
string spells_in_book(int book, int* value);

void table_of_spells()
{
    ofstream file;
    file.open("wiki_spell_table.txt");
    file << "return {\n";
    for (spell_type spell = SPELL_FIRST_SPELL; spell < NUM_SPELLS; spell++)
    {
        if (is_player_book_spell(spell) && !spell_removed(spell))
        {
            file << spell_table_entry(spell);
        }
    }
    file << "}\n";
    file.close();
}

string spell_table_entry(spell_type spell)
{
    string descript = getLongDescription(string(spell_title(spell)) + " spell");
    descript.pop_back(); // Remove final newline
    descript = regex_replace(descript, regex("\n"), "<br>");
    int minrange = _seekspell(spell)->min_range;
    int maxrange = _seekspell(spell)->max_range;
    return make_stringf(
        "  [\"%s\"] = {\n"
        "    books = {\n%s    },\n"
        "    description = \"%s\",\n"
        "    flags = {\n%s    },\n"
        "    level = %d,\n"
        "    name = \"%s\",\n"
        "    noise = { casting = %d, effect = %d },\n"
        "    [\"power cap\"] = %d,\n"
        "%s"
        "    schools = {\n%s    },\n"
        "  },\n",
        spell_title(spell),
        spell_books(spell).c_str(),
        descript.c_str(),
        spell_flag_list(spell).c_str(),
        spell_difficulty(spell),
        spell_title(spell),
        spell_noise(spell), spell_effect_noise(spell),
        spell_power_cap(spell),
        maxrange <= 0 ? "" : make_stringf("    range = { max = %d, min = %d },\n", maxrange, minrange).c_str(),
        spell_schools(spell).c_str()
        );
}

string spell_books(spell_type spell)
{
    string books = "";
    for (int i = 0; i < NUM_BOOKS; i++)
    {
        for (spell_type each : spellbook_templates[i])
        {
            if (each == spell)
            {
                book_type this_book = static_cast<book_type>(i);
                const char * this_book_name = book_name(this_book);
                if (*this_book_name)
                {
                    books += "      [\"";
                    books += book_name(this_book);
                    books += "\"] = true,\n";
                }
            }
        }
    }
    return books;          
}

string spell_schools(spell_type spell)
{
    string desc = "";
    for (const auto bit : spschools_type::range())
    {
        if (spell_typematch(spell, bit))
        {
            desc += "      ";
            desc += spelltype_long_name(bit);
            desc += " = true,\n";
        }
    }

    return desc;
}

string spell_flag_list(spell_type spell)
{
    string desc = "";
    for (const auto bit : spell_flags::range())
    {
        if(get_spell_flags(spell) & bit)
        {
            desc += "      ";
            desc += flag_name(static_cast<spflag>(bit));
            desc += " = true,\n";
        }
    }
    return desc;
}

const char * book_name(book_type book)
{
    switch (book)
    {
    case BOOK_NECRONOMICON:
        return "Necronomicon";
    case BOOK_GRAND_GRIMOIRE:
        return "Grand Grimoire";
    case BOOK_EVERBURNING:
    // Aus. English apparently follows the US spelling, not UK.
        return "Everburning Encyclopedia";
    case BOOK_MAXWELL:
        return "Maxwell's Memoranda";
    case BOOK_YOUNG_POISONERS:
        return "Young Poisoner's Handbook";
    case BOOK_FEN:
        return "Fen Folio";
    case BOOK_THERE_AND_BACK:
        return "There-And-Back Book";
    case BOOK_BIOGRAPHIES_II:
        return "Great Wizards, Vol. II";
    case BOOK_BIOGRAPHIES_VII:
        return "Great Wizards, Vol. VII";
    case BOOK_TRISMEGISTUS:
        return "Trismegistus Codex";
    case BOOK_UNRESTRAINED:
        return "the Unrestrained Analects";
    case BOOK_SIEGECRAFT:
        return "Compendium of Siegecraft";
    case BOOK_CONDUCTIVITY:
        return "Codex of Conductivity";
    case BOOK_CONSTRUCTION:
        return "Handbook of Applied Construction";
    case BOOK_TRAPS:
        return "Treatise on Traps";
    case BOOK_SWAMP_SOJOURN:
        return "My Sojourn through Swampland";
    case BOOK_MINOR_MAGIC:            return "book of Minor Magic";
    case BOOK_CONJURATIONS:           return "book of Conjurations";
    case BOOK_FLAMES:                 return "book of Flames";
    case BOOK_FROST:                  return "book of Frost";
    case BOOK_WILDERNESS:             return "book of the Wilderness";
    case BOOK_FIRE:                   return "book of Fire";
    case BOOK_ICE:                    return "book of Ice";
    case BOOK_SPATIAL_TRANSLOCATIONS: return "book of Spatial Translocations";
    case BOOK_HEXES:                  return "book of Hexes";
    case BOOK_LIGHTNING:              return "book of Lightning";
    case BOOK_DEATH:                  return "book of Death";
    case BOOK_MISFORTUNE:             return "book of Misfortune";
    case BOOK_SPONTANEOUS_COMBUSTION: return "book of Spontaneous Combustion";
    case BOOK_BATTLE:                 return "book of Battle";
    case BOOK_NECROMANCY:             return "book of Necromancy";
    case BOOK_CALLINGS:               return "book of Callings";
    case BOOK_AIR:                    return "book of Air";
    case BOOK_WARP:                   return "book of the Warp";
    case BOOK_ANNIHILATIONS:          return "book of Annihilations";
    case BOOK_UNLIFE:                 return "book of Unlife";
    case BOOK_GEOMANCY:               return "book of Geomancy";
    case BOOK_EARTH:                  return "book of the Earth";
    case BOOK_POWER:                  return "book of Power";
    case BOOK_CANTRIPS:               return "book of Cantrips";
    case BOOK_PARTY_TRICKS:           return "book of Party Tricks";
    case BOOK_DEBILITATION:           return "book of Debilitation";
    case BOOK_DRAGON:                 return "book of the Dragon";
    case BOOK_BURGLARY:               return "book of Burglary";
    case BOOK_DREAMS:                 return "book of Dreams";
    case BOOK_TRANSMUTATION:          return "book of Transmutation";
    case BOOK_BEASTS:                 return "book of Beasts";
    case BOOK_SPECTACLE:              return "book of Spectacle";
    case BOOK_WINTER:                 return "book of Winter";
    case BOOK_SPHERES:                return "book of the Spheres";
    case BOOK_ARMAMENTS:              return "book of Armaments";
    case BOOK_DECAY:                  return "book of Decay";
    case BOOK_DISPLACEMENT:           return "book of Displacement";
    case BOOK_SENSES:                 return "book of the Senses";
    case BOOK_BLASTING:               return "book of Blasting";
    case BOOK_IRON:                   return "book of Iron";
    case BOOK_TUNDRA:                 return "book of the Tundra";
    case BOOK_MOON:                   return "book of the Moon";
    case BOOK_STORMS:                 return "book of Storms";
    case BOOK_WEAPONS:                return "book of Weapons";
    case BOOK_SLOTH:                  return "book of Sloth";
    case BOOK_BLOOD:                  return "book of Blood";
    case BOOK_DANGEROUS_FRIENDS:      return "book of Dangerous Friends";
    case BOOK_TOUCH:                  return "book of Touch";
    case BOOK_CHAOS:                  return "book of Chaos";
    case BOOK_HUNTER:                 return "book of the Hunter";
    case BOOK_SCORCHING:              return "book of Scorching";
    case BOOK_MOVEMENT:               return "book of Movement";
    case BOOK_WICKED_CREATION:        return "book of Wicked Creation";
    case BOOK_MALADIES:               return "book of Maladies";
    case BOOK_FORTRESS:               return "book of the Fortress";
    case BOOK_CRYOFORMATION:          return "book of Cryoformation";
    case BOOK_GRAVE:                  return "book of the Grave";
    case BOOK_METALWORKING:           return "book of Metalworking";
    case BOOK_DUALITY:                return "book of Duality";
    case BOOK_CONTRAPTIONS:           return "book of Contraptions";
    case BOOK_RANDART_LEVEL:          return "book of Fixed Level";
    case BOOK_RANDART_THEME:          return "book of Fixed Theme";
    default:                          return "";
    }
}

const char * flag_name(spflag flag)
{
    switch (flag)
    {
    case spflag::none: return "";
    case spflag::dir_or_target: return "dir_or_target";
    case spflag::target: return "target";
    case spflag::prefer_farthest: return "prefer_farthest";
    case spflag::obj: return "obj";
    case spflag::helpful: return "helpful";
    case spflag::aim_at_space: return "aim_at_space";
    case spflag::not_self: return "not_self";
    case spflag::unholy: return "unholy";
    case spflag::unclean: return "unclean";
    case spflag::chaotic: return "chaotic";
    case spflag::hasty: return "hasty";
    case spflag::silent: return "silent";
    case spflag::escape: return "escape";
    case spflag::recovery: return "recovery";
    case spflag::area: return "area";
    case spflag::destructive: return "destructive";
    case spflag::selfench: return "selfench";
    case spflag::monster: return "monster";
    case spflag::needs_tracer: return "needs_tracer";
    case spflag::noisy: return "noisy";
    case spflag::testing: return "testing";
    case spflag::utility: return "utility";
    case spflag::no_ghost: return "no_ghost";
    case spflag::cloud: return "cloud";
    case spflag::WL_check: return "WL_check";
    case spflag::mons_abjure: return "mons_abjure";
    case spflag::not_evil: return "not_evil";
    case spflag::holy: return "holy";
    default: return "there_was_a_problem_with_my_program";
    }
}

void table_of_spellbooks()
{
    ofstream file;
    file.open("wiki_spellbook_table.txt");
    file << "return {\n";
    for (int book = 0; book < NUM_BOOKS; book++)
    {
        const char * this_book_name = book_name((book_type) book);
        if (*this_book_name)
        {
            file << spellbook_table_entry(book);
        }
    }
    file << "}\n";
    file.close();
}

string spellbook_table_entry(int book)
{
    const char * this_book_name = book_name((book_type) book);
    string that_book_name = string(this_book_name);
    string descript = getLongDescription(lowercase_string(that_book_name));
    descript.pop_back(); // Remove final newline
    descript = regex_replace(descript, regex("\n"), "<br>");
    int value = 0;
    string spells = spells_in_book(book, &value);
    return make_stringf(
        "  [\"%s\"] = {\n"
        "    description = \"%s\",\n"
        "    name = \"%s\",\n"
        "    spells = {\n%s    },\n"
        "    value = %d,\n"
        "  },\n",
        this_book_name,
        descript.c_str(),
        this_book_name,
        spells.c_str(),
        value
    );
}

string spells_in_book(int book, int* value)
{
    string ret = "";
    for (spell_type spell : spellbook_templates[book])
    {
        *value += 20 + 20 * spell_difficulty(spell);
        ret += "      \"";
        ret += spell_title(spell);
        ret += "\",\n";
    }
    return ret;
}

void wiki_table_of_spells()
{
    table_of_spells();
    table_of_spellbooks();
}
