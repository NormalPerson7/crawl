#pragma once

#include "tag-version.h"

enum duration_type
{
    DUR_INVIS,
    DUR_CONF,
    DUR_PARALYSIS,
    DUR_SLOW,
    DUR_MESMERISED,
    DUR_HASTE,
    DUR_MIGHT,
    DUR_BRILLIANCE,
    DUR_AGILITY,
    DUR_FLIGHT,
    DUR_BERSERK,
    DUR_POISONING,

    DUR_CONFUSING_TOUCH,
#if TAG_MAJOR_VERSION == 34
    DUR_SURE_BLADE,
#endif
    DUR_CORONA,
    DUR_DEATHS_DOOR,

#if TAG_MAJOR_VERSION == 34
    DUR_FIRE_SHIELD,
    DUR_BUILDING_RAGE,
#endif
    DUR_EXHAUSTED,              // fatigue counter for berserk

    DUR_STICKY_FLAME,
    DUR_ICY_ARMOUR,
#if TAG_MAJOR_VERSION == 34
    DUR_REPEL_MISSILES,
    DUR_JELLY_PRAYER,
#endif
    DUR_PIETY_POOL,             // distribute piety over time
    DUR_DIVINE_VIGOUR,          // duration of Ely's Divine Vigour
    DUR_DIVINE_STAMINA,         // duration of Zin's Divine Stamina
    DUR_DIVINE_SHIELD,          // remaining charges of TSO's Divine Shield
#if TAG_MAJOR_VERSION == 34
    DUR_REGENERATION,
#endif
    DUR_SWIFTNESS,
#if TAG_MAJOR_VERSION == 34
    DUR_CONTROLLED_FLIGHT,
#endif
    DUR_TELEPORT,
#if TAG_MAJOR_VERSION == 34
    DUR_CONTROL_TELEPORT,
#endif
    DUR_BREATH_WEAPON,
    DUR_TRANSFORMATION,
    DUR_DEATH_CHANNEL,
#if TAG_MAJOR_VERSION == 34
    DUR_DEFLECT_MISSILES,
    DUR_PHASE_SHIFT,
    DUR_SEE_INVISIBLE,
    DUR_EXCRUCIATING_WOUNDS,
#endif
    DUR_DEMONIC_GUARDIAN,       // demonic guardian timeout
    DUR_POWERED_BY_DEATH,
    DUR_SILENCE,
#if TAG_MAJOR_VERSION == 34
    DUR_CONDENSATION_SHIELD,
    DUR_MAGIC_ARMOUR,
    DUR_GOURMAND,
    DUR_BARGAIN,
    DUR_INSULATION,
#endif
    DUR_RESISTANCE,
#if TAG_MAJOR_VERSION == 34
    DUR_SLAYING,
#endif
    DUR_STEALTH,
#if TAG_MAJOR_VERSION == 34
    DUR_MAGIC_SHIELD,
#endif
    DUR_SLEEP,
#if TAG_MAJOR_VERSION == 34
    DUR_TELEPATHY,
#endif
    DUR_PETRIFIED,
    DUR_LOWERED_WL,
    DUR_REPEL_STAIRS_MOVE,
    DUR_REPEL_STAIRS_CLIMB,
    DUR_CLOUD_TRAIL,
    DUR_SLIMIFY,
    DUR_TIME_STEP,
    DUR_ICEMAIL_DEPLETED,       // Wait this many turns for Icemail to return
#if TAG_MAJOR_VERSION == 34
    DUR_MISLED,
#endif
    DUR_QUAD_DAMAGE,
    DUR_AFRAID,
#if TAG_MAJOR_VERSION == 34
    DUR_MIRROR_DAMAGE,
    DUR_SCRYING,
#endif
    DUR_VORTEX,
    DUR_LIQUEFYING,
    DUR_HEROISM,
    DUR_FINESSE,
#if TAG_MAJOR_VERSION == 34
    DUR_LIFESAVING,
#endif
    DUR_STUN_IMMUNITY,
#if TAG_MAJOR_VERSION == 34
    DUR_DARKNESS,
#endif
    DUR_PETRIFYING,
#if TAG_MAJOR_VERSION == 34
    DUR_SHROUD_OF_GOLUBRIA,
#endif
    DUR_VORTEX_COOLDOWN,
#if TAG_MAJOR_VERSION == 34
    DUR_NAUSEA,
#endif
    DUR_AMBROSIA,
#if TAG_MAJOR_VERSION == 34
    DUR_TEMP_MUTATIONS,
#endif
    DUR_DISJUNCTION,
    DUR_VEHUMET_GIFT,
#if TAG_MAJOR_VERSION == 34
    DUR_BATTLESPHERE,
#endif
    DUR_SENTINEL_MARK,
    DUR_SICKENING,
    DUR_WATER_HOLD,
#if TAG_MAJOR_VERSION == 34
    DUR_WATER_HOLD_IMMUNITY,
#endif
    DUR_FLAYED,
#if TAG_MAJOR_VERSION == 34
    DUR_RETCHING,
#endif
    DUR_WEAK,
    DUR_DIMENSION_ANCHOR,
#if TAG_MAJOR_VERSION == 34
    DUR_ANTIMAGIC,
    DUR_SPIRIT_HOWL,
    DUR_INFUSION,
#endif
    DUR_FUGUE,
#if TAG_MAJOR_VERSION == 34
    DUR_SONG_OF_SHIELDING,
#endif
    DUR_TOXIC_RADIANCE,
    DUR_RECITE,
    DUR_GRASPING_ROOTS,
#if TAG_MAJOR_VERSION == 34
    DUR_SLEEP_IMMUNITY,
#endif
    DUR_FIRE_VULN,
    DUR_ELIXIR,
#if TAG_MAJOR_VERSION == 34
    DUR_ELIXIR_MAGIC,
    DUR_ANTENNAE_EXTEND,
#endif
    DUR_TROGS_HAND,
    DUR_BARBS,
    DUR_POISON_VULN,
    DUR_FROZEN,
    DUR_SAP_MAGIC,
#if TAG_MAJOR_VERSION == 34
    DUR_MAGIC_SAPPED,
#endif
    DUR_DIMENSIONAL_BULLSEYE,
    DUR_FORESTED,
    DUR_DRAGON_CALL,
    DUR_DRAGON_CALL_COOLDOWN,
#if TAG_MAJOR_VERSION == 34
    DUR_ABJURATION_AURA,
#endif
    DUR_MESMERISE_IMMUNE,
    DUR_NO_POTIONS,
    DUR_QAZLAL_FIRE_RES,
    DUR_QAZLAL_COLD_RES,
    DUR_QAZLAL_ELEC_RES,
    DUR_QAZLAL_AC,
    DUR_CORROSION,
#if TAG_MAJOR_VERSION == 34
    DUR_FORTITUDE,
#endif
    DUR_HORROR,
    DUR_NO_SCROLLS,
#if TAG_MAJOR_VERSION == 34
    DUR_NEGATIVE_VULN,
#endif
    DUR_CLEAVE,
    DUR_GOZAG_GOLD_AURA,
#if TAG_MAJOR_VERSION == 34
    DUR_COLLAPSE,
    DUR_BRAINLESS,
    DUR_CLUMSY,
    DUR_DEVICE_SURGE,
#endif
    DUR_DOOM_HOWL,
#if TAG_MAJOR_VERSION == 34
    DUR_DOOM_HOWL_IMMUNITY,
#endif
    DUR_VERTIGO,
    DUR_ANCESTOR_DELAY,
    DUR_SANGUINE_ARMOUR,
    DUR_NO_CAST,
    DUR_CHANNEL_ENERGY,
    DUR_SPWPN_PROTECTION,
    DUR_NO_HOP,
    DUR_HEAVENLY_STORM,
    DUR_DEATHS_DOOR_COOLDOWN,
    DUR_BERSERK_COOLDOWN,
    DUR_RECITE_COOLDOWN,
    DUR_ACROBAT,
#if TAG_MAJOR_VERSION == 34
    DUR_SHAFT_IMMUNITY,
#endif
    DUR_NOXIOUS_BOG,
    DUR_FROZEN_RAMPARTS,
#if TAG_MAJOR_VERSION == 34
    DUR_STABBING,
#endif
    DUR_ATTRACTIVE,
#if TAG_MAJOR_VERSION == 34
    DUR_LOCKED_DOWN,
#endif
    DUR_WORD_OF_CHAOS_COOLDOWN,
    DUR_SICKNESS,
    DUR_BLINKBOLT_COOLDOWN,
#if TAG_MAJOR_VERSION == 34
    DUR_DUEL_COMPLETE,
#endif
    DUR_RISING_FLAME,
    DUR_BLINK_COOLDOWN,
    DUR_OOZEMANCY,
    DUR_FIERY_ARMOUR,
    DUR_ANIMATE_DEAD,
#if TAG_MAJOR_VERSION == 34
    DUR_CORPSE_ROT,
#endif
    DUR_NO_MOMENTUM,
    DUR_ENLIGHTENED,
    DUR_REVELATION,
    DUR_SIPHON_COOLDOWN,
    DUR_JINXBITE,
#if TAG_MAJOR_VERSION == 34
    DUR_BINDING_SIGIL_WARNING,
#endif
    DUR_JINXBITE_LOST_INTEREST,
    DUR_VITRIFIED,
    DUR_RAMPAGE_HEAL,
    DUR_CANINE_FAMILIAR_DEAD,
    DUR_TEMP_CLOUD_IMMUNITY,
    DUR_VILE_CLUTCH,
    DUR_ALLY_RESET_TIMER,       // 5-turn buffer to cancel 'stop attack' order
    DUR_BEOGH_DIVINE_CHALLENGE,
    DUR_BEOGH_CAN_RECRUIT,
    DUR_BEOGH_SEEKING_VENGEANCE,
    DUR_BLOOD_FOR_BLOOD,
    DUR_FATHOMLESS_SHACKLES,
    DUR_CONSTRICTION_IMMUNITY,
    DUR_GAVOTTE_COOLDOWN,
    DUR_FUSILLADE,
    DUR_PRIMORDIAL_NIGHTFALL,
    DUR_BLIND,
    DUR_SIGN_OF_RUIN,
    DUR_GRAVE_CLAW_RECHARGE,
    DUR_INFERNAL_LEGION,
    DUR_CELEBRANT_COOLDOWN,
    DUR_EXECUTION,
    DUR_GROWING_DESTRUCTION,
    DUR_EPHEMERAL_SHIELD,
    DUR_TIME_WARPED_BLOOD_COOLDOWN,
    DUR_SPIKE_LAUNCHER_ACTIVE,
    DUR_PARAGON_ACTIVE,
    DUR_FORTRESS_BLAST_TIMER,
    DUR_PHALANX_BARRIER,
    DUR_BLINKITIS,
    DUR_VAINGLORY,
    DUR_VEXED,
    DUR_TRICKSTER_GRACE,
    DUR_CACOPHONY,
    DUR_DROWSY,
    DUR_ENKINDLED,
    DUR_SHROUD_TIMEOUT,
    DUR_DETONATION_CATALYST,
    DUR_RIME_YAK_AURA,
    DUR_AUTODODGE,
    NUM_DURATIONS
};
