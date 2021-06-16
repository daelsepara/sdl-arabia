#ifndef __STORY__HPP__
#define __STORY__HPP__

#include <vector>

#include "constants.hpp"
#include "controls.hpp"
#include "codewords.hpp"
#include "items.hpp"
#include "skills.hpp"
#include "character.hpp"

namespace Choice
{
    enum class Type
    {
        NORMAL = 0, // No requirements
        ITEMS,
        GET_ITEMS,
        SKILL,
        CODEWORD,
        MONEY,
        LIFE,
        ANY_ITEM,
        ANY_SKILL,
        SKILL_ITEM,
        SKILL_ANY,
        SKILL_ALL,
        FIRE_WEAPON,
        LOSE_ITEMS,
        LOSE_MONEY,
        LOSE_ALL,
        LOSE_SKILLS,
        GET_CODEWORD,
        LOSE_CODEWORD,
        GAIN_MONEY,
        GIVE,
        BRIBE,
        TAKE,
        PAY_WITH,
        SELL,
        BARTER
    };

    class Base
    {
    public:
        const char *Text = NULL;

        Choice::Type Type = Choice::Type::NORMAL;

        Skill::Type Skill = Skill::Type::NONE;

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        std::vector<Codeword::Type> Codewords = std::vector<Codeword::Type>();

        int Value = 0;

        int Destination = -1;

        Base(const char *text, int destination)
        {
            Text = text;
            Destination = destination;
        }

        Base(const char *text, int destination, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL_ITEM;
            Items = items;
            Skill = skill;
        }

        Base(const char *text, int destination, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::ITEMS;
            Items = items;
        }

        Base(const char *text, int destination, Skill::Type skill)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL;
            Skill = skill;
        }

        Base(const char *text, int destination, std::vector<Codeword::Type> codewords)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::CODEWORD;
            Codewords = codewords;
        }

        Base(const char *text, int destination, Choice::Type type, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type)
        {
            Text = text;
            Destination = destination;
            Type = type;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Skill = skill;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Codeword::Type> codewords)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Codewords = codewords;
        }
    };
} // namespace Choice

namespace Story
{
    enum class Type
    {
        NORMAL = 0,
        GOOD,
        SORROW,
        DOOM
    };

    enum class Controls
    {
        NONE = 0,
        STANDARD,
        SHOP,
        BUY_AND_SELL,
        SELL,
        TRADE,
        BARTER,
        BARTER_AND_SHOP
    };

    class Base
    {
    public:
        int ID = 0;

        const char *Text = NULL;

        const char *Title = NULL;

        const char *Bye = NULL;

        const char *Image = NULL;

        Story::Controls Controls = Story::Controls::NONE;

        std::vector<Choice::Base> Choices = std::vector<Choice::Base>();

        std::vector<std::pair<Item::Base, int>> Shop = std::vector<std::pair<Item::Base, int>>();
        std::vector<std::pair<Item::Base, int>> Sell = std::vector<std::pair<Item::Base, int>>();

        std::pair<Item::Base, Item::Base> Trade;
        std::vector<std::pair<Item::Base, std::vector<Item::Base>>> Barter = std::vector<std::pair<Item::Base, std::vector<Item::Base>>>();

        // Player selects items to take up to a certain limit
        std::vector<Item::Base> Take = std::vector<Item::Base>();

        // Player selects items to lose
        std::vector<Item::Base> ToLose = std::vector<Item::Base>();

        int Limit = 0;

        int LimitSkills = 0;

        Story::Type Type = Story::Type::NORMAL;

        // Handle background events
        virtual int Background(Character::Base &player) { return -1; };

        // Handle events before story branches
        virtual void Event(Character::Base &player){};

        // Jump to next section
        virtual int Continue(Character::Base &player) { return -1; };

        Base()
        {
        }

        Base(int id)
        {
            ID = id;
        }

        Base(int id, const char *text, Story::Type type)
        {
            ID = id;
            Text = text;
            type = type;
        }

        Base(const char *text, Story::Type type)
        {
            Text = text;
            type = type;
        }
    };

    std::vector<Button> StandardControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/exit.png", idx + 4, idx + 5, compact ? idx + 5 : 1, idx + 5, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ShopControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> SellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/selling.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BuyAndSellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/selling.png", idx + 5, idx + 7, compact ? idx + 6 : 1, idx + 6, startx + 6 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 7, "icons/exit.png", idx + 6, idx + 7, compact ? idx + 7 : 1, idx + 7, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> TradeControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::TRADE));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BarterControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/exhange.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::BARTER));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BarterAndShopControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/exchange.png", idx + 5, idx + 7, compact ? idx + 6 : 1, idx + 6, startx + 6 * gridsize, buttony, Control::Type::BARTER));
        controls.push_back(Button(idx + 7, "icons/exit.png", idx + 6, idx + 7, compact ? idx + 7 : 1, idx + 7, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ExitControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/exit.png", compact ? idx : idx - 1, idx, compact ? idx : idx - 1, idx, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }
} // namespace Story

class NotImplemented : public Story::Base
{
public:
    NotImplemented()
    {
        ID = -1;

        Title = "Not implemented yet";

        Controls = Story::Controls::NONE;
    }
};

auto notImplemented = NotImplemented();

auto Stories = std::vector<Story::Base *>();

void *findStory(int id)
{
    Story::Base *story = &notImplemented;

    if (Stories.size() > 0)
    {
        for (auto i = 0; i < Stories.size(); i++)
        {
            if (((Story::Base *)Stories[i])->ID == id)
            {
                story = (Story::Base *)Stories[i];

                break;
            }
        }
    }

    return story;
}

class Prologue : public Story::Base
{
public:
    Prologue()
    {
        ID = 0;

        Title = "Prologue";

        Image = "images/filler3.png";

        Text = "After many days on the road, it is with a quickening of the blood that you breathe in and catch the ripe, enticing scent of Baghdad's canal-irrigated orchards in the distance. Cresting a hill, you rein in your horse and gaze down on the city of your birth. There is a haze in the air that, filtering the shafts of morning sunlight, makes the gardens and marble palaces seem as though flecked with gold. Beyond the city walls, the River Tigris laces between the green fields and the woodland of the hunting parks like a vein of liquid fire.\n\nThe horse whinnies and tugs at the reins.\n\n\"You like the look of that fresh grass, eh, Antar?\"\n\nYou pat his mane and dismount, leading him to a spot where he can graze in the shade. Then you lie back to bask in the warm sun. Bees drone lazily amid the flowers. You set out early this morning and have made good speed. Why not enjoy a nap before riding on into the city?\n\nYet sleep does not come. You are too excited. When you set out a month ago to attend your uncle's funeral, you were contented but poor, with few prospects for the future. You never dreamt that your uncle, whom you hardly knew, had made you his heir. He left you his fine stallion Antar, who has already become a firm friend. And in your saddlebags are bars of gold that will allow you to set yourself up in whatever enterprise you wish.\n\nAs you muse on what you will do with your new-found fortune, you become aware of voices on the other side of the hill. Antar is still contentedly chewing the grass. Moved by curiosity, you make your way through the bushes and look down to see a group of servants laying out a picnic. Nearby stand soldiers, obviously the guards of a plump nobleman in elegant robes who has a hawk that he sends swooping down the hill. Each time the bird falls on a field mouse, the nobleman's ample belly quakes with cruel laughter.\n\nOne of the soldiers comes up to the nobleman and salutes him. You are close enough to hear him say, \"Lord Jafar, shall we set up your pavilion?\"\n\nYou know that name. Jafar is the Grand Vizier of Baghdad, who advises the Caliph on every detail of state policy. You decide to remainout of sight. It is not prudent to attract the attention of one so rich and powerful. He could easily decide you are trespassing and have you flogged or enslaved.\n\nJafar nods, then waves the soldier away and beckons over a thin servant clad in black who had been standing aloof from the others. The servant hovers beside Jafar with a fixed grin on his face, like a worshipper waiting to hear the word of his god.\n\nJafar sends the hawk aloft and watches it. Then he says thoughtfully, as though to himself, \"Every night, the Caliph puts on ordinary clothes and has me lead him by means of secret passages to explore the streets outside the palace walls. In this way, he hopes to learn the true will of the people.\"\n\n\"It's all too easy for a ruler to get out of touch,\" puts in the black-clad servant.\n\nJafar nods. \"Precisely. Lately I have been leading the Caliph to very select venues -- inns and houses where I have previously planted my own agents. They talk of rebellion, and the Caliph hears their talk, and gradually he begins to believe that his subjects hate him.\"\n\n\"Oh, a scheme of rare cunning, if I may say so, your excellency,\" says the servant. \"But where's it leading, may I ask?\"\n\n\"The Caliph, fearing rebellion, each day grows more cautious, more paranoid. He intensifies the rule of law and deals harshly with those whose loyalty is in question. And so, by fearing rebellion, each day he brings it closer.\"\n\nThe servant claps his hands in delight. \"You are the Prince of Guile, my lord! So the populace will come to hate the noble Caliph...\"\n\n\"And then, when the time is ripe, I'll overthrow him. How the people will cheer! Despite my humble protests, they'll insist that I take the place of the despot. Can you see it, Natar?\"\n\n\"I can, excellency!\" cries the servant. \"And when you are Caliph, what then?\"\n\nHe waits with an expectant smile which fades as he sees the dark look in Jafar's eyes.\n\n\"And then?\" says Jafar grimly. \"Then the whole world shall tremble.\"\n\nYou've heard more than enough. This many secrets can get a person killed. You are edging back into the bushes when one of Jafar's guards comes around the hill. Outrage leaps like fire into your blood. The guard is leading your horse.\n\n\"See what I found, excellency,\" he says, taking the horse over to Jafar.\n\n\"Thank you,\" purrs Jafar, patting Antar's neck. \"A fine gift.\"\n\nThis is too much to bear. Striding down the hill, you raise your hand and call out. \"Wait! That's my horse.\"\n\nJafar flicks his gaze vaguely in your direction, looking through you as though you are nothing. \"I believe the horse is mine, and yet I seemed to hear a voice raised in protest. How can the Grand Vizier of Baghdad be mistaken?\"\n\nYou are almost choking with emotion. You lunge, seizing Antar's reins. \"This is outright theft!\"\n\nNow Jafar glares. His eyes, like tiny crystals of ice, focus on yours. You shudder at the sudden palpable wave of evil. \"Justice is not for the likes of you,\" he spits. \"I make the law here.\"\n\nThe servant, Natar, peers at you and then speaks anxiously to his master: \"This wretch may have overheard us, lord. Shall I..?\"\n\nHe draws his knife half out of its sheath.\n\nJafar nods. Before you can react, one of the guards clubs you across the back of the neck. Your legs give way and they catch you under the arms. Natar pushes the knife towards you.\n\n\"Not here,\" snaps Jafar. \"You'll get blood over the picnic things. Do it by the river, then throw the body in.\"\n\nYou are half-led, half-dragged towards the riverbank. You're groggy but you fight to stay conscious, knowing that if you black out now you will never awaken. The river surges past below. Natar's face swims close through waves of nausea. The knife approaches your throat.\n\nYou muster a burst of strength and break free of the guards holding you. Natar only laughs. \"So, you still have some fight left in you. Good.\"\n\nYou seize his wrist, but you know you don't have the strength to disarm him. Instead you let your legs give way, using your dead weight to drag you both over the side of the bank.\n\nIcy cold water engulfs you. Natar's grin has become a mask of hatred and alarm. By luck you twist the knife around, and you think you managed to cut him. He is swept away and you tumble with thecurrent, spinning down and down into a black sink of oblivion.\n\nYou are revived by the last rays of the sun. You are lying in river mud near to some fishermen's hovels on the outskirts of the city.\n\nIgnoring the throb in your skull, you drag yourself to your feet and stumble along the warren of streets, your only thought being to stay hidden. Jafar's agents may already be looking for you. With what you have learned, your days are numbered. Unless you can expose Jafar as the villain he is.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 1; }
};

class Story001 : public Story::Base
{
public:
    Story001()
    {
        ID = 1;

        Text = "Nightfall finds you walking aimlessly through the narrow back streets of the city. From off in the main plaza you can hear the hubbub of street entertainers and night-time revellers. Torchlight flares from braziers set up for the festival. Here the street is hushed and dimly lit. You shrink back into the shadows, preferring to be alone with your bitter thoughts.\n\nA beggar sits in a doorway, unnoticed by the few passers-by. He is an old dervish with a streaked grey beard. He reaches out his tin cup, startling you, and you flinch at the sight of his scabrous hands. Then you see the green turban that marks him as a hajji -- one who has made the arduous pilgrimage to Mecca.\n\n\"Alms for the love of God,\" he mutters.\n\nAshamed at the feeling of loathing that swept across your face at first, you fish in your pocket and GIVE him a dinar. It rattles in his cup and for a moment he peers at it as though it were a wondrous vision. He gestures up at the heavens and says, \"You have only to lift your head: there is a sight to banish misfortune. Under the wide sky, God sees all and guides the worthy to a just reward.\"\n\nThe remark seems filled with portent. You gaze up past the rooftops at the stars: a thousand lights sharp as jewels on the cloth of the night. A feeling of awe at their beauty takes the breath from your body. By the time you look back, the dervish is shuffling away.\n\nYou follow him to the end of the alley, but lose sight of him as he slips through a crowd of people who are gathered to hear a storyteller. As the storyteller finishes his tale, the crowd begins to break up. Some move off towards a troupe of acrobats from distant Cathay whose oiled flesh gleams like amber in the flaring torchlight. Others go to buy sweetmeats from stalls around the plaza. The storyteller sits back on his mat, beaming at the mound of coins he has earned.\n\nYou are standing outside an astrologer's shop. A man emerges, brushing past you, nodding with a smile as he catches your eye. The tattoo on his chest suggests he is a sailor.";

        Choices.clear();
        Choices.push_back(Choice::Base("Enter the astrologer's shop", 69));
        Choices.push_back(Choice::Base("Talk to the sailor", 475));
        Choices.push_back(Choice::Base("Go over to the storyteller", 23));
        Choices.push_back(Choice::Base("Go in search of the elusive dervish", 92));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, -1);
    }
};

class Story002 : public Story::Base
{
public:
    std::string PreText = "";

    Story002()
    {
        ID = 2;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "There is a clang as your SWORD strikes the floor, followed by an ominous hush as Masrur steps forward smiling and pins your arms behind your back. You are taken to the dungeons, stripped of everything you own, then hung in chains and tortured for several days.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        Character::LOSE_ALL(player);

        if (player.Life > 0)
        {
            PreText += "\n\nYou are finally released and half-dragged to the docks by a captain of the Palace Guard. \"As you value your life, wretch, take ship from Baghdad on this very hour,\" he snarls. \"Jafar won't be so lenient the next time.\"\nHe turns on his heel and walks away, leaving you clutching a stanchion for support. He is right. You must leave Baghdad -- at least until your regain your strength. Then you can come back for revenge.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story003 : public Story::Base
{
public:
    Story003()
    {
        ID = 3;

        Text = "\"Perhaps this tale is true, perhaps not. Only God knows all,\" begins the old storyteller. \"It concerns a young prince who, while travelling in the wilderness, came to a hut of mud bricks. Drawing water from the well, he was taken unawares by two strong brothers who came upon him from behind. They carried him to their mother, an aged crone with a face as withered as a rotten gourd. Her teeth were like broken pebbles, her eyes filmy with rheum. And the prince knew from their white skin that these were not mortals, but a family of ghouls. Then he feared for his life, but even in his terror his wits did not entirely desert him. ''Am I to die without a chance to save myself?'' he asked as they stoked the fire.\n\nThe ancient she-ghoul leered as she sprinkled the seasoning. ''What chance would you have?'' she asked. ''In any contest, my sons are superior to a mortal man.''\n\n''I have no skill with weapons,'' replied the prince. ''But in my own land I am famous as an athlete. Why not set me free with a head start? Then, if your sons are fleet of foot, they can try to hunt me down. They will return with good appetites, and no scraps at the table will go to waste.''\"\n\nThe captain has come over and heard part of this tale. Butting in, he turns to you and says, \"Why waste your time on this foolishness? This is a tale for the witless. Does this old man think us as credulous as any village peasant?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Agree with the captain", 375));
        Choices.push_back(Choice::Base("Hear the rest of the story", 74));

        Controls = Story::Controls::STANDARD;
    }
};

class Story004 : public Story::Base
{
public:
    Story004()
    {
        ID = 4;

        Text = "If not for Ayisha's magic, Jafar would have achieved a last act of villainy from beyond the grave, for the venom on his knife was lethal and even an antidote would not save any ordinary man. But, weaving her fingers over the wound, she calls the poison out in the form of green vapour which the Caliph's servants catch in a bottle.\n\nThe Caliph sits up, amazed to be alive.\n\n\"As long as the bottle remains stoppered, father, you are safe.\"\n\n\"Then place it in our deepest vaults,\" he commands the captain of the guard. \"God is merciful to return my daughter to me, and surely it is by His hand that she saved my life.\"\n\nAyisha glances at you. \"I had help, O my father.\"\n\nThe Caliph nods and beckons you closer.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 120; }
};

class Story005 : public Story::Base
{
public:
    std::string PreText = "";

    Story005()
    {
        ID = 5;

        Choices.clear();
        Choices.push_back(Choice::Base("Take advantage of the momentary respite to retreat to the top of the steps and flee into the tunnel", 408));
        Choices.push_back(Choice::Base("Extinguish the taper", 449));
        Choices.push_back(Choice::Base("Try racing for the bottom of the steps", 73));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The creatures swoop down. They are like giant moths with the faces of dead men, and their wings have the smell of grave shrouds. The first of them reaches you. You can see lice writhing in its coarse dusty fur. It lands on your shoulder and bites, tearing your flesh.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        if (player.Life > 0)
        {
            PreText += "\n\nYou give a cry of disgust and swat it away, your punch shattering the sequin-like facets of its eye. It spirals down into the depths, but the others are not far away.";
        }

        Text = PreText.c_str();
    }
};

class Story006 : public Story::Base
{
public:
    Story006()
    {
        ID = 6;

        Text = "Yussuf finds you wandering along the harbour front. \"I thought you must have set sail without me,\" you say, grinning with relief.\n\n\"Not at all!\" he declares. \"But I must confess, I am surprised to see you here in the north docks. Did you forget that we are moored over yonder, in the south docks?\"\n\nYou rub your face to hide a rueful grimace. Your career as a sailor has not got off to a very promising start.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go back to the ship with Yussuf", 431));
        Choices.push_back(Choice::Base("Decide that a life at sea is not for you after all", 81));

        Controls = Story::Controls::STANDARD;
    }
};

class Story007 : public Story::Base
{
public:
    std::string PreText = "";

    Story007()
    {
        ID = 7;

        Choices.clear();
        Choices.push_back(Choice::Base("Agree", 53));
        Choices.push_back(Choice::Base("Run for your life", 30));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You give a gasp of pain as the gryphon rips out your left eye.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nSuddenly filled with renewed strength, the gryphon goes bounding across the hall and claws the monstrous goat to the floor. When its foe stops twitching, it looks up and seems about to speak, only to look around as a third foe emerges from the inner recesses of the palace. This is a great snake as long as a ship, with venom running like stagnant water from its fangs. Its eyes burn red as the fires of Iblis the Despairer, lord of all evil spirits.\n\nYou look at the wounded gryphon. \"What now?\" you ask with a groan.\n\n\"Now,\" it says wearily, \"the only way I can hope for victory is to drink the marrow of a human thigh-bone.\"\n\nHorror of horrors!";
        }

        Text = PreText.c_str();
    }
};

class Story008 : public Story::Base
{
public:
    Story008()
    {
        ID = 8;

        Text = "You step into the next room. The shutters are all closed and the only light comes from resinous torches. The haze of pungent smoke makes your eyes water. Blinking as your vision adjusts to the shadows, you see the natives crouching with heads bowed towards the far end of this long room. Your captain stands there as though on trial -- his judges, two rows of silent figures draped in rugs, which they wear like heavy robes.\n\n\"What's this farce?\" you thunder. \"Release my captain or suffer the consequences, you worthless heathen dogs.\"\n\nThat seems to goad them into action. They leap up with flashing eyes and bear down on you armed with spears and knives. You back into the doorway and get ready for a fight.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 54; }
};

class Story009 : public Story::Base
{
public:
    Story009()
    {
        ID = 9;

        Text = "There is indeed a tingle of recuperative energy as you taste the delicious crisp FRUIT on your tongue.\n\nThe merchant was as good as his word -- almost as great a miracle in itself as the magic healing. You gaze longingly at his stock of APPLEs. These are a prize worth more than gold to a daring adventurer like yourself.\n\n\"You'd like to buy more?\" he asks.\n\nYou try not to appear too eager. \"At five dinars each? Recovery from one serious sword-blow would require enough fruit to pauper me!\"\n\n\"Perhaps we can barter,\" he suggests.";

        Choices.clear();
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 1);

        Shop.clear();

        if (Character::VERIFY_ITEMS_ANY(player, {Item::CLOAK, Item::JEWELLED_SWORD, Item::BLACK_JEWEL, Item::HAWK}))
        {
            Controls = Story::Controls::STANDARD;
        }
        else
        {
            Shop = {{Item::GOLDEN_APPLE, 5}};

            Controls = Story::Controls::SHOP;
        }
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS_ANY(player, {Item::CLOAK, Item::JEWELLED_SWORD, Item::BLACK_JEWEL, Item::HAWK}))
        {
            return 55;
        }
        else
        {
            return 32;
        }
    }
};

class Story010 : public Story::Base
{
public:
    Story010()
    {
        ID = 10;

        Text = "You have not forgotten the tale you heard from the old storyteller in the village.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::CONCH);
    }

    int Continue(Character::Base &player) { return 469; }
};

class Story011 : public Story::Base
{
public:
    Story011()
    {
        ID = 11;

        Text = "You fall in with a merchant caravan that is heading north along the coast of the Red Sea. The owner is pleased to have a fellow traveller who can help guard his camels.\n\n\"Pirates are the main threat to trade,\" he says, \"but even on the pilgrim routes close to Mecca there is still the danger of bandits. They ride out of the desert to prey on honest traders like myself.\"\n\nDespite his fears, the first couple of weeks pass without incident. You get used to the disdainful snorting of the camels as they are roused each morning, struggling resentfully to their feet and slowly filing out along the coast road. To the right lies a range of mountains of dull velvet hue, to the left is the glassy glint of the sea. You RECOVER 2 Life Points.\n\nOn the sixteenth day you come in sight of the walls of Mecca, the holy city, birthplace of the Prophet. Pilgrims flock from all over the civilized world as a sign of their devotion. But the merchant, Hakim, is reluctant to stop here.\n\n\"Another time I will show my respect,\" he says. \"Indeed, perhaps I will visit Mecca on my return journey. But for now, look at my camels -- they are heavily laden with goods that I am anxious to sell in Cairo. I cannot afford the ten days it would take to complete all the proper rituals here.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Urge him to stop at Mecca", 101));
        Choices.push_back(Choice::Base("You can see his point", 123));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 2);
    }
};

class Story012 : public Story::Base
{
public:
    Story012()
    {
        ID = 12;

        Image = "images/filler2.png";

        Text = "The braziers burn low while you see to your silent work. At last, with everything ready, you summon your marines ashore and together you set up a great shout which reverberates off the roof of the dome. The pirates rouse themselves to find that you have bound them all tightly with torn strips of silk.\n\n\"What devil's work's this?\" demands the pirate chief. \"How did you truss us like so many geese without waking us up?\"\n\n\"Too much wine made you sleep as quiet as babies,\" you reply, \"and I am a skilful thief. But in all honesty, I'll admit to one mistake.\" You tilt your head towards a single pirate who lies stretched out stiffly with a jewelled dagger in his chest. \"He had the bad luck to wake up. Now he sleeps the soundest sleep of all.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 372; }
};

class Story013 : public Story::Base
{
public:
    Story013()
    {
        ID = 13;

        Text = "You decide on your options.";

        Choices.clear();
        Choices.push_back(Choice::Base("Lunge at him with all your strength", 148));
        Choices.push_back(Choice::Base("Dive to one side as he attacks and just attempt a light slash in return", 37));
        Choices.push_back(Choice::Base("Concentrate on parrying", 60));

        Controls = Story::Controls::STANDARD;
    }
};

class Story014 : public Story::Base
{
public:
    Story014()
    {
        ID = 14;

        Text = "Fate smiles on you. An old acquaintance from Baghdad recognizes you among the crowd of pilgrims and hastens to greet you. Hakim is astonished and not a little put out when he learns that you are a devout believer. It means that he will have to free you from bondage. Also, it means that you too can enter the holy city for the ceremonies.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::MORDANT);
    }

    int Continue(Character::Base &player) { return 146; }
};

class Story015 : public Story::Base
{
public:
    std::string PreText = "";

    Story015()
    {
        ID = 15;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Another few days brings you to Zeila, a medium-sized port on the west coast of the Gulf of Adan. The journey has been arduous, and it has been a long time since you had a drink of water.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE) && !Character::VERIFY_ITEMS(player, {Item::Type::WATER_BOTTLE}))
        {
            Character::GAIN_LIFE(player, -1);

            PreText += "\n\nYou LOSE 1 Life Point.";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nRefreshing yourself at a fountain by the city gates, where you can refill any bottles you are carrying, you hear a sublimely beautiful song wafting through the dusk. It is the call to prayer from the high minaret you can see above the rooftops. Kneeling where you are, you give thanks to heaven for seeing you safely through the desert.";

            Character::REFILL(player, Item::Type::WATER_BOTTLE);
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 149; }
};

class Story016 : public Story::Base
{
public:
    Story016()
    {
        ID = 16;

        Text = "The storm hits like a black fist, stretching the sails to bursting point. Rain lances down in a suffocating icy torrent. Waves surge up over the rail until you could almost believe it was the world's end, and you had plunged into unending watery oblivion.\n\nBy dint of every trick and ploy you've learned in your long career at sea, you weather the storm. The next morning finds you drifting on water as flat as a silver mirror. The silence of extreme fatigue hangs over the whole ship's company. The sails hang in ragged tatters and the mizzen has split, but at least no one was lost during the night.\n\nYou report to the captain that there is a chance of hitting more squalls if you continue on your present course.\n\n\"You're recommending we turn back?\" he asks listlessly.\n\nYou shrug. \"That may or may not be safer. You're the captain.\" He laughs bitterly. His pride has taken a knock. \"Compared to you, I'm as green as any street urchin! You decide our course.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Head on to the Indies", 197));
        Choices.push_back(Choice::Base("Turn west towards Egypt", 176));
        Choices.push_back(Choice::Base("Strike out south in search of the Scarlet Isle", 234));

        Controls = Story::Controls::STANDARD;
    }
};

class Story017 : public Story::Base
{
public:
    Story017()
    {
        ID = 17;

        Text = "You vow that you will kill them if they do not leave you in peace. \"You have the claws of a cat, youngster,\" says the Sultan, his voice half-mocking, \"but the voice of a lion. Choose: will you fight my three Arab knights, or face me alone?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Accept a duel with the Sultan himself", 222));
        Choices.push_back(Choice::Base("Square off against his knights", 245));

        Controls = Story::Controls::STANDARD;
    }
};

class Story018 : public Story::Base
{
public:
    Story018()
    {
        ID = 18;

        Text = "The old man studies your slippers intently. \"Such intricate embroidery,\" he says. \"I don't think I have ever seen finer workmanship. Surely these slippers are no ordinary footwear?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell him about the MAGIC SLIPPERS", 87, {Item::MAGIC_SLIPPERS}));
        Choices.push_back(Choice::Base("Do not tell him", 61));

        Controls = Story::Controls::STANDARD;
    }
};

class Story019 : public Story::Base
{
public:
    Story019()
    {
        ID = 19;

        Text = "You return to the throne room to find a scene of deep sorrow. The Caliph's wives are weeping over his body. Even from beyond the grave, Jafar managed a last act of treachery when the poison on his knife reached the Caliph's heart.\n\nThe royal court is in chaos. No one knows who is in charge. In circumstances like this people often look for a scapegoat, so you do not wait around in the hope of a reward. Slipping off in the confusion, you fetch your horse and leave Baghdad that very night. No doubt there are other adventures awaiting you in the far corners of the world.";

        Type = Story::Type::SORROW;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story020 : public Story::Base
{
public:
    Story020()
    {
        ID = 20;

        Text = "Now that the danger is over, you find you are trembling in shock. You sit on the end of Ayisha's couch while you recover. \"Where did you learn sorcery?\"\n\n\"My old nurse taught me,\" she replies, smiling. \"Alas, she never told me any spell to undo these enchanted chains.\"\n\n\"There must be a key.\"\n\nAyisha nods. \"There is. It is in the nest of the giant bird known as the rokh. If you'd agree to try and get it, I could send you there with another spell I know.\" She pauses and adds hesitantly, \"It would be dangerous, of course.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Agree to try", 114));
        Choices.push_back(Choice::Base("You must bid farewell to Ayisha", 66));

        Controls = Story::Controls::STANDARD;
    }
};

class Story021 : public Story::Base
{
public:
    Story021()
    {
        ID = 21;

        Text = "The Isle of Palms is a wild windswept place off the southern tip of India. Putting into a cove, you wade ashore. \"We'll wait here,\" says Umar, the sailor in charge of the boat. \"If you're not back by daybreak tomorrow then, er, well...\"\n\nYou nod. \"I'll be back.\"\n\nThe interior of the island consists of grassy slopes surrounding a high pinnacle of rock whose peak is hidden in the clouds. Seeing sheep grazing in a valley nearby, you saunter over and find a shepherd who tells you, \"Yes, the rokh's nest is atop that pinnacle. Have you come to slay it?\"\n\nYou give an astonished laugh. \"Hardly. From what I've heard, that would take an army.\"\n\nThe shepherd shrugs. \"Pity. It's forever stealing my sheep -- swoops down, grabs one, then carries it back to its nest.\"\n\n\"Maybe you should go and live elsewhere.\"\n\n\"Preposterous! The grass here is the richest to be found in all the world. See how plump my sheep are, the quality of their wool.\"\n\nThanking the shepherd for his help, you head towards the pinnacle.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 146; }
};

class Story022 : public Story::Base
{
public:
    Story022()
    {
        ID = 22;

        Text = "The chamberlain receives you with an unctuous smile. \"You wish to see the Caliph?\" he says. \"Naturally it is not quite as simple as that. There are many complicated arrangements in the running of a palace. When the Caliph gives an audience, a hundred officials are sent into a flurry of activity. I myself am only one cog in the wheel.\"\n\nYou know what is expected: a gift of gold.";

        Choices.clear();
        Choices.push_back(Choice::Base("Offer 1000 dinars or less", 443, Choice::Type::MONEY, 0));
        Choices.push_back(Choice::Base("Offer more than 1000 dinars", 426, Choice::Type::MONEY, 1001));
        Choices.push_back(Choice::Base("You have no money to give: you are ejected from the palace at once -- and promptly arrested for breaking the curfew", 405));

        Controls = Story::Controls::STANDARD;
    }
};

class Story023 : public Story::Base
{
public:
    Story023()
    {
        ID = 23;

        Text = "The storyteller invites you to sit with him and take a cup of tea. Soon you find yourself blurting out the whole day's sorry tale, ending with your encounter with the dervish.\n\nHe listens with a sympathetic smile. \"Truly, there is wisdom in the words of a holy man.\"\n\nYou shrug. \"If so, I lack the wisdom to discern it. What can he have meant? It seemed from his tone that he was issuing a prophecy.\"\n\n\"He spoke of the rokh,\" says the storyteller, raising a finger to the sky. \"It is a bird as large as a whale. The beating of the rokh's wings moves the clouds above our heads. Its eyrie pierces the vault of heaven, and elephants are its prey.\"\n\n\"What is that to me? The mere stuff of idle yarns.\"\n\nHe shakes his head. \"This is a story that has its basis in truth. It is said -- though only God is all-knowing -- that the egg laid by the rokh is of pure diamond. One fragment would make a man as rich as a prince. If you seek wealth, find the rokh's nest.\"\n\nThe storyteller is ready to entertain another audience, so you thank him for the tea and say goodbye. The sailor you saw earlier is standing nearby, watching a street magician pull coloured ribbons from a young girl's ears.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go over and introduce yourself", 475));
        Choices.push_back(Choice::Base("Go off to ponder your next move", 92));

        Controls = Story::Controls::STANDARD;
    }
};

class Story024 : public Story::Base
{
public:
    std::string PreText = "";

    Story024()
    {
        ID = 24;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You start to stoop as if you're going for the sword, then roll forward and rush past Masrur as he lunges at you. Taken by surprise, he lashes out clumsily. Even so the tip of the blade bites deep into your shoulder, causing a flare of pain.\n\nYou LOSE 3 Life Points.";

        Character::GAIN_LIFE(player, -3);

        if (player.Life > 0)
        {
            PreText += "\n\nMasrur thunders with rage at not having killed you with one blow. You do not wait around to give him another chance. Clutching your bleeding shoulder, you dash out onto the landing.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 207; }
};

class Story025 : public Story::Base
{
public:
    Story025()
    {
        ID = 25;

        Image = "images/bedouin-chieftain.png";

        Text = "The man who stands before you is as lean and muscular as a leopard. He wears the garb of a splendid Bedouin chieftain. His burnoose is clasped by a golden scorpion sting, and his silver belt is patterned like snakeskin. The pommel of his long curved sword is an ivory vulture's head. He looks down at you with a thunderhead gaze and says, \"Direct your prayers to me, mortal. Not that I care a whit for them.\"\n\nDespite your chattering teeth, you manage to ask his name.\n\n\"I am the Lord of the Desert. I have ruled this desolate region since the beginning of time. I am as merciful as the sun and as comforting as the rocks, as truthful as a mirage and as temperate as a sandstorm.\"\n\nWhile he proudly declaims all this, you are careful to avert your eyes so that you can look around the chamber. It is a grand treasure-hall, with tall jars of spices and perfumed oils, rugs and drapes of lushly coloured silk, as well as gold and silver coins that shimmer like rain droplets in the lamplight.\n\nThere are only two possible exits. One is a flight of steps leading up to a locked door banded with iron. The other is a curtained alcove with a strange glyph stamped into the keystone above it.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 287;
        }
        else
        {
            return 309;
        }
    }
};

class Story026 : public Story::Base
{
public:
    Story026()
    {
        ID = 26;

        Text = "The captain is grumpy at being woken. \"Why does God ordain that the sun shall set at dusk and rise again at dawn?\" he says sarcastically. \"It is because He wishes the same for us. It reminds me of the parable of the holy man who was so tormented by the screech of owls outside his window at night that he gave up his vows and became a drunkard.\"\n\n\"Would you rather I let you snore like a contented camel while river pirates steal upon us in the night-time? Or perhaps while wizards cast a spell on us?\" You take him by the arm. \"Come and see what I have to show you.\"\n\nWhen you lead him to the rail, however, there is no sign of the silent barque.\n\n\"All you saw was the reflection of moonlight on the water,\" snaps the captain. \"Go back to your mattress and let us all get some sleep.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 375; }
};

class Story027 : public Story::Base
{
public:
    Story027()
    {
        ID = 27;

        Text = "In his hurry to get away, Yussuf stumbles into you and the taper falls to the floor. You try to shove him away so that you can retrieve it, but it gets trodden underfoot. Darkness descends like a raven'S wing.\n\nOut of the dreadful heart-stopping silence, the only sound to be heard is the ragged rasp of Yussuf's sobbing. \"Merciful God, spare your unworthy servant,\" he pleads. \"Never will I thieve nor cheat at dice again. No drop of wine will touch my lips--\"\n\n\"Yussuf, listen!\" You reach out a hand and shake him until he gathers his wits.\n\n\"There's nothing ...\" he says in a voice of budding hope. \"What happened to the monsters?\"\n\nStepping forward to look for the taper, you tread on something which squelches under your heel. As Yussuf picks up and relights the taper, you see that you have crushed a swarm of beetles.\n\n\"There are the monsters.\"\n\nYussuf gasps in wonder. \"Tiny insects! But the things we saw were huge.\"\n\n\"Magical mirages. The terrors of our own minds were almost turned against us.\" You peer into the gloom ahead. \"We must be on our guard, my friend. This is a place of dark sorcery.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 186; }
};

class Story028 : public Story::Base
{
public:
    Story028()
    {
        ID = 28;

        Text = "You have the cool nerve of a born acrobat. The precarious descent holds no terrors for you. With surefooted agility you continue to the bottom of the staircase.\n\n\"Come on,\" you call back to Yussuf. \"It isn't far.\"\n\n\"Even less so if I fall,\" he whines. \"Let me make the descent at my own speed.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 96; }
};

class Story029 : public Story::Base
{
public:
    Story029()
    {
        ID = 29;

        Text = "After a few days you have to accept that the ship has sailed without you. You consider signing on aboard another ship, but by now you are so well known around the docks for having lost your ship that people there have given you the nickname Faramush -- meaning dimwit. The best job you could hope for would be swabbing the decks. You decide instead to join a camel train.\n\nYou find a merchant called Hakim who is heading across the desert to Cairo. He will pay you 3 dinars to come along and guard his wares. Another merchant, by the name of Abdullah, wishes to travel east through the Peaks of the Slayers and is prepared to pay 5 dinars. The rates of pay give you a clue as to how dangerous the respective journeys are likely to be.";

        Choices.clear();
        Choices.push_back(Choice::Base("Join Hakim's expedition", 400, Choice::Type::GAIN_MONEY, 3));
        Choices.push_back(Choice::Base("Go with Abdullah", 296, Choice::Type::GAIN_MONEY, 5));

        Controls = Story::Controls::STANDARD;
    }
};

class Story030 : public Story::Base
{
public:
    std::string PreText = "";

    Story030()
    {
        ID = 30;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "";

        if (Character::VERIFY_SKILL(player, Skill::Type::ARCHERY))
        {
            Character::LOSE_SKILLS(player, {Skill::Type::ARCHERY});

            PreText += "Your ARCHERY skill is LOST.\n\n";
        }

        PreText += "You could never judge your aim now that you have only one eye. You must console yourself with the thought that you are still alive. Also, once you get an eye patch you will at least look the part of a true sailor.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 402; }
};

class Story031 : public Story::Base
{
public:
    Story031()
    {
        ID = 31;

        Text = "Hurriedly tipping the grisly remains out of into the street, you roll yourself up inside the rug. The slimy residue left on the fabric has a sepulchral stench, but you try not to think about it. As the two men pick you up, you hear one of them whisper, \"The one in here must be Remorak, Lord of the Razana. Better not drop him!\"\n\nYou are carried into the next room and sat on a wooden bench. The flap of the rug falls open like a cowl, allowing you to see with one eye as the men who brought you in go scurrying over to join the other islanders cringing on the floor. The room is heady with the aromatic smoke of sputtering resin torches.\n\nYou look along the bench. Other figures, also wrapped in rugs, sit along the wall. You catch a glimpse of a thin dirt-caked hand, a skeletal gleam of a face within the cowl beside you. It is a council of the dead.\n\nCaptain Ibrahim steps forward. \"Why have I been treated like this?\" he demands as he looks along the row of silent rug-draped forms. He is pale despite his show of bravado.\n\nIs it your imagination, or does one of the forms stir slightly? You barely hear a whispering crackle of a voice: \"You came to steal the rokh's diamond egg from its nest above the Nile.\"\n\nThe captain jerks back his head in denial. \"The rokh? The giant bird of legend? Stuff and nonsense. How can I feed my family on imaginary wealth? I came here for honest trade.\"\n\nSome of the cowled figures sway together like long stalks of grass after the rain. You cannot tell if they are really moving or whether it is a trick of the shimmering smoke-hazed light. Nor do you want to know if you really can hear that soft susurration of tomb-cold voices. The villagers are still prostrate on the floor with their faces pressed to the wooden boards. It's time you did something.\n\n\"The foreign sailor is lying,\" you say in your best attempt at a corpse's voice. \"I, Remorak, will prove it will my magic. All avert your eyes! Raise your voices in prayer to your ancestors!\"\n\nThey commence a chant that drowns out any other sounds as you shrug off the musty rug and hurriedly lead your amazed captain to the door.\n\nYou gained the codeword KISMET.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});
    }

    int Continue(Character::Base &player) { return 145; }
};

class Story032 : public Story::Base
{
public:
    Story032()
    {
        ID = 32;

        Text = "Each of the GOLDEN APPLEs will heal 1 lost Life Point when eaten. You cannot eat APPLEs to bring you back from the dead, of course -- if you go below zero Life Points at any stage of the adventure then you are dead, regardless of whether you may have magic APPLEs still uneaten in your backpack.";

        Bye = "Thanking the fruit seller, you head back to the ship.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 78; }
};

class Story033 : public Story::Base
{
public:
    Story033()
    {
        ID = 33;

        Text = "Your blow splits the ghoul's head like a gourd. Whatever spills out is not like any human brain: a quivering black mass that reminds you of a dead octopus. Retching, you cast the wooden stick aside and hastily search the hut for anything worth taking. You find 15 dinars in a jar over the hearth -- money no doubt stolen from the poor souls the ghouls waylaid and ate.\n\nYou also take a thick woollen CLOAK. You have no desire to spend the night here, and you will need something to keep warm while sheltering amid the rocks. The CLOAK is crawling with lice, but you hold it over the fire for a few minutes so that the smoke drives most of them out.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 15);

        Take = {Item::CLOAK};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 80; }
};

class Story034 : public Story::Base
{
public:
    Story034()
    {
        ID = 34;

        Text = "The ghoul dam looks up with bulging eyes as the door splinters under your kick. \"What have you done to my sons?\" she screeches before lunging towards a meat cleaver hanging on the wall.\n\nA worm-eaten old stick rests beside the door.";

        Choices.clear();
        Choices.push_back(Choice::Base("Grab it and attack her", 435));
        Choices.push_back(Choice::Base("Use a SWORD", 391, Choice::Type::ANY_ITEM, {Item::SWORD, Item::JEWELLED_SWORD}));
        Choices.push_back(Choice::Base("Rely on your bare hands", 413));

        Controls = Story::Controls::STANDARD;
    }
};

class Story035 : public Story::Base
{
public:
    Story035()
    {
        ID = 35;

        Text = "You go and shelter in a cave, after first checking that it isn't already occupied. A raw wind howls outside, but you are snug inside your woollen CLOAK. Even so, you get very little sleep after your horrific experience. Rising with the first silver light of the predawn, you head down out of the hills to join the others.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 289; }
};

class Story036 : public Story::Base
{
public:
    Story036()
    {
        ID = 36;

        Text = "It feels as though the wind is blasting your skin dry. You wrap your turban across your face and stumble on, barely able to see. There is no way you could hear the others even if they shouted. The tug of the other camels on the ropes is the only reassurance that you are not entirely alone in this ordeal.\n\nYou LOSE 1 Life Point.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head straight into the storm", 105));
        Choices.push_back(Choice::Base("Veer off to the left", 82));
        Choices.push_back(Choice::Base("Veer off to the right", 59));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }
};

class Story037 : public Story::Base
{
public:
    Story037()
    {
        ID = 37;

        Text = "His blade whips around, carving a livid streak across your breastbone. Your own blow had no effect on him.\n\nYou LOSE 2 Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to close in for a desperate full-strength attack", 148));
        Choices.push_back(Choice::Base("Lunge at him from arm's length", 106));
        Choices.push_back(Choice::Base("Retreat while parrying", 60));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }
};

class Story038 : public Story::Base
{
public:
    Story038()
    {
        ID = 38;

        Text = "You explain to the old man that there has been a mistake. You are not the one who stole the Sultan'S ruby.\n\nSurprisingly, his answer to this is a thin wheeze of laughter. \"Not the Shadow, eh? I thought not. I doubt they'll ever catch that one.\"\n\n\"Who is the Shadow?\"\n\n\"The most daring of knaves. The rogue who purloined the jinn RING of Ala al-Din and the flying rug once owned by the Emir of Cordoba, as well as the crown of the infidel ruler Shah al Ma'in. He -- or she, for the Shadow is a figure veiled in mystery -- has vowed next to steal the diamond egg of the rokh.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::KISMET}))
        {
            return 64;
        }
        else
        {
            return 470;
        }
    }
};

class Story039 : public Story::Base
{
public:
    Story039()
    {
        ID = 39;

        Text = "You drank the poisoned water soon after coming aboard. Assuming the hawser was cut soon after, and judging the time now to be midmorning, you have been drifting for about fourteen hours. Allowing for the breeze and ocean current, you quickly estimate how far the ship has covered in that period.\n\nIt is hard work raising the sails on your own, but you have the advantage of long nautical experience. Bringing the ship around, you steer towards your best guess of where the other ship would have reached by dawn. You know that your friends will sail back looking for you once they find you've been set adrift. Not out of sentiment, of course. It's just that nothing would stop Captain Ibrahim from retrieving a free cargo of glass and porcelain.\n\nUnless he and the crew have already been poisoned themselves, that is.\n\nYou keep on searching the horizon as the sun reaches its zenith, then sinks down the sky. Finally your persistence is rewarded by the sight of your own ship plunging through the waves towards you. As she comes alongside, you leap across to a great cheer from the crew.\n\nOnce you've warned the captain that he probably has a stowaway on board, he orders the ship thoroughly searched. Soon there are shouts from the hold, and a small plump man in a long robe is dragged on deck. \"He was hiding behind one of the crates,\" says the first mate. \n\nThe stowaway fixes you with a resentful stare. \"Curse you! How did you sail that ship back on your own? If not for you, I'd have poisoned the water tonight and made myself master of the vessel.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 174; }
};

class Story040 : public Story::Base
{
public:
    Story040()
    {
        ID = 40;

        Text = "The riders are close behind. You scramble up a bank of loose earth, buying yourself a little time. Pushing through a thicket of mauve ferns, you arrive at a deep ravine whose depths are filled with haze. The ravine is spanned by a great glass column. You place a foot down to test it, finding it very slippery.\n\nThe thunder of hoofbeats warns you that the riders are searching for a way to follow.";

        Choices.clear();
        Choices.push_back(Choice::Base("Risk crossing the glass column", 63));
        Choices.push_back(Choice::Base("Stand and wait to confront them here, with your back to the sheer drop", 86));

        Controls = Story::Controls::STANDARD;
    }
};

class Story041 : public Story::Base
{
public:
    Story041()
    {
        ID = 41;

        Text = "His eyes widen as he notices the bundle of ROPE over your shoulder. \"I travelled far and wide in my youth,\" he says. \"Now, don't tell me -- let me guess. That's Indian hemp, isn't it? I saw some bizarre little conjuring tricks that used a coil of ROPE just like that, during my time in the east.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell him about the INDIAN ROPE trick", 110, {Item::INDIAN_ROPE}));
        Choices.push_back(Choice::Base("Remain silent", 61));

        Controls = Story::Controls::STANDARD;
    }
};

class Story042 : public Story::Base
{
public:
    Story042()
    {
        ID = 42;

        Text = "You travel on until you come to the sea. Walking along the shore, you approach a fishing village where men squat on the sand mending their nets. You are about to go up and greet them when you notice a slender young fellow crouching beside an overturned boat. He has only one hand, the other arm ending in a bandaged stump, and he is crying.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stop to talk to him", 135));
        Choices.push_back(Choice::Base("Walk past", 492));

        Controls = Story::Controls::STANDARD;
    }
};

class Story043 : public Story::Base
{
public:
    Story043()
    {
        ID = 43;

        Text = "Your jinni utters a last forlorn cry which echoes in the air as he fades into wisps of torn vapour. The  RING is useless now that the jinni has been destroyed.\n\nAzenomei leans back gasping against the wall. Now, while he is still stunned from the fight with the jinni, you have a chance to act.";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack him", 423));
        Choices.push_back(Choice::Base("Run for it", 445));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::RING});
    }
};

class Story044 : public Story::Base
{
public:
    Story044()
    {
        ID = 44;

        Text = "This far down the slope, you are in no immediate danger from lava. The deadly hot gases spewed out of the volcano are another matter. They move faster than a cheetah can run, and that dark cloud you can see would bake the flesh off your bones in seconds.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 90; }
};

class Story045 : public Story::Base
{
public:
    Story045()
    {
        ID = 45;

        Text = "Using the magic lamp to turn invisible, you sneak right under the noses of the sentries, along a gallery lined with officials and slaves, past the Caliph's bodyguard, and into the throne room where Harun al-Rashid sits dining on delicate morsels of food. Nearby stands Jafar, an attentive smile masking his thoughts of treachery.\n\nExtinguishing the light, you suddenly become visible. Harun leaps up with a start. \"God protect me from evil magic!\" he cries.\n\n\"Wait, O Prince of the Faith,\" you say, bowing to kiss the floor in front of him. \"I am no jinni, but your loyal subject. Hear my words.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 477; }
};

class Story046 : public Story::Base
{
public:
    std::string PreText = "";

    Story046()
    {
        ID = 46;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The demon pursues you into the covered passage. It realizes its mistake when you leap on it. Here it cannot retreat into the air every few seconds to recuperate from its wounds. \"Bad move, devil,\" you snarl as you pound it with heavy blows, \"now you've got to fight fair.\"\n\nThe demon's talons scrape you to the bone, but you give two blows for every one that it inflicts.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -1;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 275; }
};

class Story047 : public Story::Base
{
public:
    std::string PreText = "";

    Story047()
    {
        ID = 47;

        Bye = "You at last reach the stairway and rush off into the safety of the night.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The Palace guards are upon you like a pack of wolves. Their standard trick is to get in close and buffet a foe with their shields, using their swords only when there is no danger of striking one another. Knowing this, you drop low and let the first guard sweep his shield over your head, immediately straightening up and using the force of your legs to propel him off the balcony. He gives a shriek as he tumbles to the floor of the hall below. But now the next two guards have reached you -- and you cannot fool them all with the same trick.\n\nJafar stands behind the guards with his flabby hands balled into fists. He is spitting with fury as he orders them to rush you, but they are in no hurry to throw their lives away.\n\nYou beat a retreat along the landing, fighting for your life every step of the way. You take several nasty wounds.\n\n";

        auto DAMAGE = -5;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -3;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 383; }
};

class Story048 : public Story::Base
{
public:
    Story048()
    {
        ID = 48;

        Text = "The barque takes shape out of the darkness. You feel like one who, sunk in slumber, witnesses the vivid colours of a dream. The sails of the barque have a satin sheen as though woven of silver. Jewels sparkle around the lamps set at her prow, and her rail is decorated with inlays of polished ivory. At the stern is a small pavilion curtained with sequined silks. As the breeze stirs the drapes and gutters the lantern-light inside, you see a woman reclining there on a cushioned divan.\n\nDo you wish to speak with her?";

        Choices.clear();
        Choices.push_back(Choice::Base("Swim out to the mysterious barque", 94));
        Choices.push_back(Choice::Base("Go to fetch the captain", 26));

        Controls = Story::Controls::STANDARD;
    }
};

class Story049 : public Story::Base
{
public:
    Story049()
    {
        ID = 49;

        Image = "images/filler4.png";

        Text = "The guards burst into the room, only to find a dead body slumped on the cold marble floor. Shrugging, they sheathe their swords. Jafar pushes his way to the front and demands to know what is going on.\n\n\"The intruder committed suicide, it seems, lord,\" says the captain of the guard, indicating the trickle of poison on your lips.\n\nJafar hisses between his teeth. \"A pity. I'd have liked to oversee the interrogation of this one.\"\n\nThe captain hides a flicker of disgust at Jafar's open cruelty. Turning away sharply, he says to the guards, \"Take this corpse to the burial-ground.\"\n\nYou are taken to the edge of the city and left in a small brick building beside the cemetery, there to await burial in the morning. When the guards have left, the jinni breathes the gust of life back into your lungs. Rubbing your stiff limbs, you get up and fix him with a sour frown. \"Why did you make them think I was dead?\"\n\nHe smiles -- at least, you think it's a smile. \"They're not going to kill you twice, are they?\"\n\n\"But why didn't you turn their swords to snakes? Or fill the room with choking fog? Or whisk me away to safety on a flying cloud?\"\n\n\"Oh, what are you complaining about?\" snaps the jinni. \"I got you out safely, didn't I?\" He becomes a twist of vapour that slowly flows back into your RING.\n\nAs you walk back from the graveyard, you consider that it might be wise to quit Baghdad for a while. The wild corners of the world are full of mystery and promise, and adventurers of olden times often returned from their travels laden with riches. If you could do the same, then you would be a better position to bring Jafar to justice. It only remains to decide your route.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go by sea", 160));
        Choices.push_back(Choice::Base("Go by land", 183));

        Controls = Story::Controls::STANDARD;
    }
};

class Story050 : public Story::Base
{
public:
    std::string PreText = "";

    Story050()
    {
        ID = 50;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "\"Come,\" says the gryphon. It leads you to a vestibule where you see a table of platinum that glints with a liquid sheen. On the table rest two objects: a sapphire the size of an eye, and a whole leg of burnished gold. Pressing the sapphire to your empty socket, you discover that you can see as well through it as you could with the eye you lost. The leg, too, knits to your flesh. It is as strong as your former limb.\n\nYou RECOVER 5 Life Points.";

        Character::GAIN_LIFE(player, 5);

        if (!Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            player.SKILLS_LIMIT++;

            player.Skills.push_back(Skill::LUCK);

            PreText += "\n\nYou have acquired the LUCK skill.";
        }

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            player.SKILLS_LIMIT++;

            player.Skills.push_back(Skill::AGILITY);

            PreText += "\n\nYou have acquired the AGILITY skill.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::JASMINE_FLOWER}))
        {
            return 98;
        }
        else
        {
            return 76;
        }
    }
};

class Story051 : public Story::Base
{
public:
    Story051()
    {
        ID = 51;

        Text = "You have crept, clambered and crawled through many places that were danker and darker than this. Your sharpened senses do not need light. You turn around to face the steps and continue the descent backwards, like a climber, moving sure-footedly until you feel the firm expanse of rock that marks the bottom of the staircase.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 96; }
};

class Story052 : public Story::Base
{
public:
    Story052()
    {
        ID = 52;

        Text = "You press on along the tunnel. The taper gives only a smouldering glow which is barely enough to see beyond arm's length. After several minutes, you begin to feel a slight breeze. \"It might be the way out,\" says Yussuf hopefully, quickening his step.\n\nYou doubt it. The air still has a stale subterranean reek. Yussuf stops abruptly with a small groan, and you hurry to join him. The tunnel has emerged at the top of a narrow stone staircase, barely two feet wide. The steps look dank and slippery. On either side is a sheer drop into darkness. You can sense an immense cavern, but the walls and ceiling and floor are too far away for the feeble light of the taper to reach. All you can see is that alarmingly narrow staircase stretching into the unseen depths below.\n\nYussuf finds a pebble and drops it off the side of the top step. Seven heartbeats later you hear it hit the floor of the cavern. He looks at you. \"We have to go down?\".";

        Choices.clear();
        Choices.push_back(Choice::Base("Turn back", 408));
        Choices.push_back(Choice::Base("Start down the staircase", 430));

        Controls = Story::Controls::STANDARD;
    }
};

class Story053 : public Story::Base
{
public:
    std::string PreText = "";

    Story053()
    {
        ID = 53;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The great beak descends, cracking open your leg. You give a great shriek of agony and sink back with a groan.\n\nYou LOSE 3 Life Points.";

        Character::GAIN_LIFE(player, -3);

        if (player.Life > 0)
        {
            PreText += "\n\nYou are barely conscious enough to witness the battle. It seems to your watery gaze as though the two monstrous adversaries are submerged in a red haze. With thundering howls and hissing war-cries, they twine and writhe in a battle that shakes the very walls around you. At last the gryphon is victorious. It comes padding across the golden tiles to your side.\n\n\"That was the last,\" it says. \"They slew my masters, who once dwelt here, but now I have avenged them.\"\n\n\"At what a cost!\" you wail. \"See me -- blinded, disfigured and crippled. Oh, merciful God, what have I done to merit such a fate?\"";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 50; }
};

class Story054 : public Story::Base
{
public:
    std::string PreText = "";

    Story054()
    {
        ID = 54;

        Choices.clear();
        Choices.push_back(Choice::Base("Fight on and try to rescue him", 122));
        Choices.push_back(Choice::Base("Flee while you still can", 145));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The islanders launch themselves on you with shrieks of fury. \"Kill the foreign devil!\" you hear the headman cry. \"It is not permitted for an outsider to gaze upon the Council of Retired Elders and live!\"\n\nTheir rage works in your favour. They are all so anxious to kill you that their attacks are too fast and too wildly aimed. Weapons clash together, or lodge in the wooden pillars, more often than they find their mark in your flesh. Even so, you are injured.\n\n";

        auto DAMAGE = -3;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -2;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nYou glance up past the throng of angry faces to see your captain standing dumbstruck against the wall. The haze of blue resin-scented smoke makes him look like a ghost in his white tunic.";
        }

        Text = PreText.c_str();
    }
};

class Story055 : public Story::Base
{
public:
    Story055()
    {
        ID = 55;

        Text = "The fruit seller will give you two GOLDEN APPLEs in exchange for each of the following items: a JEWELLED SWORD, a CLOAK, a HAWK, or a BLACK JEWEL. You can get up to eight APPLEs if you have all these items and are prepared to part with them.\n\nYou can also buy additional GOLDEN APPLEs at 5 dinars each if you have any money left.";

        Choices.clear();

        Controls = Story::Controls::BARTER_AND_SHOP;
    }

    void Event(Character::Base &player)
    {
        Shop = {{Item::GOLDEN_APPLE, 5}};

        Barter = {
            {Item::JEWELLED_SWORD, {Item::GOLDEN_APPLE, Item::GOLDEN_APPLE}},
            {Item::CLOAK, {Item::GOLDEN_APPLE, Item::GOLDEN_APPLE}},
            {Item::HAWK, {Item::GOLDEN_APPLE, Item::GOLDEN_APPLE}},
            {Item::BLACK_JEWEL, {Item::GOLDEN_APPLE, Item::GOLDEN_APPLE}}};
    }

    int Continue(Character::Base &player) { return 32; }
};

class Story056 : public Story::Base
{
public:
    Story056()
    {
        ID = 56;

        Text = "You remember the tale of a man who was captured by a family of ghouls. To save his life, he challenged the two sons to a race. Securing a head start, he hid himself in a thorn bush until they ran past and then doubled back to the hut where their mother was preparing supper. He knew he had to kill her, otherwise her sorcery would find him wherever he ran. Luckily he also knew that steel cannot kill a ghoul witch; only a wooden weapon will do. Taking up a stick, he gave her a single good clout that dashed out her brains. And it was good for him that his first blow was decisive, because although a ghoul can be hurt with one blow, a second blow will only heal its wounds.";

        Bye = "Armed with this knowledge...";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 469; }
};

class Story057 : public Story::Base
{
public:
    Story057()
    {
        ID = 57;

        Text = "An ominous cough breaks the silence of the night. You whirl around. Your heart sinks when you see the ghoulish witch and her sons standing right behind you. She is pointing a divining rod in your direction, saying through gritted teeth: \"There's your supper. Don't lose it again!\"\n\nShe clouts you across the face with the rod. Lose 1 Life Point. If you still live, you are gripped firmly by the arms and led back to the hut. They shove you into the pantry and the mother starts looking at the jars along the shelves. \"Let's see... a bit of pepper and some garlic ought to set off the flavours nicely.\"\n\nThis is your last chance.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [MAGIC]", 327, Skill::Type::MAGIC));
        Choices.push_back(Choice::Base("Go down fighting", 305));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            Choices[1].Destination = 370;
        }
        else
        {
            Choices[1].Destination = 305;
        }
    }
};

class Story058 : public Story::Base
{
public:
    std::string PreText = "";

    Story058()
    {
        ID = 58;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "You pick your way between the sleeping pirates, open-mouthed at the wealth carelessly scattered all around. In your amazement you fail to notice their ship's cat curled up on a pile of velvet cushions. You tread on its tail and there is a howl that rises to the high domed roof. In seconds the pirates are on their feet, staring around in shock and fury.\n\nBefore you have a chance to call out to your marines, one of the pirates raises an earthenware jug and sloshes its oily contents all over you. On contact with the air, the oil bursts into flame. You are engulfed in Greek fire -- the sticky chemical used in sea battles. If you can't put it out quickly, you'll be burned alive.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nEven diving into the water will not save you -- you are charred to a blackened crisp in seconds, and that is the end of your adventure.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 488; }
};

class Story059 : public Story::Base
{
public:
    std::string PreText = "";

    Story059()
    {
        ID = 59;

        Choices.clear();
        Choices.push_back(Choice::Base("Go straight into the teeth of the storm", 105));
        Choices.push_back(Choice::Base("Head right", 128));
        Choices.push_back(Choice::Base("Head left", 82));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Weak, deafened by the shriek of the wind and blinded by the driven sand, you stumble onwards. Desperation drives you to keep going. If you fell, you know that you would soon be buried beneath the dunes.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou still have the strength to press on.";
        }

        Text = PreText.c_str();
    }
};

class Story060 : public Story::Base
{
public:
    std::string PreText = "";

    Story060()
    {
        ID = 60;

        Choices.clear();
        Choices.push_back(Choice::Base("Parry his next blow", 129));
        Choices.push_back(Choice::Base("Try for a long-reach stab at his wrist", 37));
        Choices.push_back(Choice::Base("Drive in close for a desperate attack", 83));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your blades clash with a deathly knell that resounds off the marble walls. His strength is incredible. Your parry is knocked aside and you are nicked painfully on the shoulder.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou fight on.";
        }

        Text = PreText.c_str();
    }
};

class Story061 : public Story::Base
{
public:
    Story061()
    {
        ID = 61;

        Text = "The oubliette is a bell-shaped chamber lined with muck and straw. There are several other prisoners here. Seeing you pacing around, one of them sighs and points to the grille in the middle of the ceiling. \"Some of us have been here for years,\" he says. \"Food is thrown down every day or so, if we're lucky. Other than that we're forgotten here. There's no escape.\"\n\n\"What about water?\"\n\n\"You must lick what you can off the walls.\" He shows you his tongue -- black and covered with sores.\n\nYou position yourself directly below the grille and stare up. A distance of almost twenty feet. The walls funnel in towards it, so there is no chance of climbing up.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use a MAGIC SLIPPERS or an INDIAN ROPE", 133, Choice::Type::ANY_ITEM, {Item::MAGIC_SLIPPERS, Item::INDIAN_ROPE}));
        Choices.push_back(Choice::Base("Try something else", 155));

        Controls = Story::Controls::STANDARD;
    }
};

class Story062 : public Story::Base
{
public:
    Story062()
    {
        ID = 62;

        Text = "The discovery of a small keg of date wine in the hold saves you from the threat of dehydration, but you are still in desperate straits. You cannot sail the ship alone. Borne on by the current, you drift for days until you see a hazy stretch of land. On getting closer, it turns out to be a region of mangrove swamps: gnarled trees with their roots surrounded by swirling salt water. You peer inland. The swamps continue as far as the eye can see.\n\nAs the ship drifts sluggishly along the shoreline, a host of hairless little monkeys come gibbering through the mangrove roots. Their skins are as smooth and blotchy as old bananas. They leap and splash through the waves towards the ship. Scrambling over the side in a crash of surf, they pilfer the lockers. You rush around trying to stop them but they are too quick. Clutching their plunder, they drop overboard and swim rapidly away.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::MAGIC))
        {
            return 220;
        }
        else
        {
            return 243;
        }
    }
};

class Story063 : public Story::Base
{
public:
    Story063()
    {
        ID = 63;

        Text = "Your foot slips on the glass surface and you plunge to your doom in the chasm far below.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 109;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::CUNNING))
        {
            return 132;
        }
        else
        {
            return -1;
        }
    }
};

class Story064 : public Story::Base
{
public:
    Story064()
    {
        ID = 64;

        Text = "\"The egg of the rokh!\" you say with a far-away look in your eye. \"I've heard its nest lies just below the clouds, atop a pinnacle overlooking the headwaters of the Nile.\"\n\n\"No doubt it is high above the ground,\" retorts the old man, \"but as for being at the head of the Nile -- nonsense! I myself was born in a village at the head of the Nile. If there had been any high peak nearby on which the rokh nested, I would surely know about it. The truth is that the rokh is to be found on the Isle of Palms, far to the east.\"\n\nYou gained the codeword FABRIC.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::KISMET);

        Character::GET_CODEWORDS(player, {Codeword::Type::FABRIC});
    }

    int Continue(Character::Base &player) { return 470; }
};

class Story065 : public Story::Base
{
public:
    Story065()
    {
        ID = 65;

        Text = "Drawing a deep breath just before the smoke cloud reaches you, you stumble blindly forward to the middle of the room. The hubble-bubble pipe is still there. Pushing the tube into your mouth, you draw air into your lungs. You guessed right. The noxious smoke, in passing through the water of the pipe, is rendered harmless.\n\nThe three sorcerers are calling to each other, but they cannot see what's happening because of the cloud of smoke. You scoop up the chart they were looking at and tuck the hubble-bubble pipe under your arm, then grope your way to the back of the room. There you find a doorway that leads out of the citadel, and you make your escape.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::CHART, Item::HUBBLE_BUBBLE_PIPE};

        Limit = 2;
    }

    int Continue(Character::Base &player) { return 42; }
};

class Story066 : public Story::Base
{
public:
    std::string PreText = "";

    Story066()
    {
        ID = 66;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::HAREM);

        PreText = "You start back across the baking desert sands. Billows of heat rise off the ground, making the horizon tremble. Rocks and dust lie in all directions as far as the eye can see.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_ITEMS(player, {Item::Type::WATER_BOTTLE}))
        {
            DAMAGE = -1;

            PreText += "Your WATER BOTTLE has been EMPTIED. ";

            Character::EMPTY(player, Item::Type::WATER_BOTTLE);
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            DAMAGE++;

            PreText += "[WILDERNESS LORE] ";
        }

        if (DAMAGE > 0)
        {
            DAMAGE = 0;
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 454; }
};

class Story067 : public Story::Base
{
public:
    Story067()
    {
        ID = 67;

        Text = "Hakim spends the next few hours sunk in silence as you travel on. He seems to be weighing something in his conscience. At last he comes to you and, with a solemn expression, produces a key with which he unlocks your slave collar. \"God would not forgive me if I kept in bondage one to whom I owe my life,\" he says.\n\n\"Cheer up,\" you say, enjoying the feel of the dry desert air against skin chafed for so long by the iron collar. \"Don't think of it as losing a slave, more as gaining a friend.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::MORDANT);
    }

    int Continue(Character::Base &player) { return 218; }
};

class Story068 : public Story::Base
{
public:
    Story068()
    {
        ID = 68;

        Text = "You come up with several plans.\n\nFirst, you could try to get to see the Caliph. You know that this would involve giving the chamberlain a gift of more than 1000 dinars to prove you're a person of high rank.\n\nSecond, you could approach someone who works at the palace and get them to take you to the Caliph in person. You know several palace employees, but you cannot be sure which of them are loyal to the Caliph himself and which are in the pay of Jafar the Vizier.\n\nThird, you know that the Caliph sometimes travels around the city in disguise at night. It ought to be possible for you to tail him and perhaps get close enough to tell him your story -- as long as his bodyguard, Masrur, doesn't kill you first.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try the first approach", 22));
        Choices.push_back(Choice::Base("Risk the second approach", 361));
        Choices.push_back(Choice::Base("Try the third approach", 182));

        Controls = Story::Controls::STANDARD;
    }
};

class Story069 : public Story::Base
{
public:
    Story069()
    {
        ID = 69;

        Text = "The astrologer emerges from his shop and stands gazing out across the plaza. The festival seems not to interest him. The crowds of merry-makers might as well be the flitting shadows of puppets. His gaze is fixed firmly on the sky, where the moon shows as a thin sliver of ivory above the spires of the city.\n\nYou step up beside him. \"Barely moments ago, a dervish spoke significantly to me of the sky's portents,\" you say. \"What can you see amid the stars?\"\n\nHe turns to look at you. His gaze is misty with secret lore. He sweeps his arm up, taking in the constellations spread out above, then ends the gesture by pointing at the door of his shop. \"The stars are the key to all mysteries, but yonder is the portal,\" he tells you. \"One dinar will oil the lock, and then you may step into your future.\"\n\nThe sudden talk of money banishes all fancies. \"Are you a sage, old man, or the father of all merchants? Have you so little heart for the beauty of the night that you must sully it with talk of money?\"\n\nHe strokes his beard. \"A dinar only! Will you balk at such a paltry price, when you have the chance to learn what the future holds?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Pay him one dinar", 115, Choice::Type::LOSE_MONEY, 1));
        Choices.push_back(Choice::Base("Talk to the sailor who just left", 475));
        Choices.push_back(Choice::Base("Talk to the storyteller sitting on the plaza nearby", 23));
        Choices.push_back(Choice::Base("Go on your way", 92));

        Controls = Story::Controls::STANDARD;
    }
};

class Story070 : public Story::Base
{
public:
    Story070()
    {
        ID = 70;

        Text = "You weave to one side, then jump back as Masrur's mighty blade comes chopping down. The blow misses you by inches, striking the floor where you were standing just a second ago. There is a harsh ringing sound as the tip of the blade snaps off, followed by Masrur's scream of scarlet rage.\n\nIf he wasn't in a killing mood before, he is now. Dodging past, you race out onto the landing. Jafar follows, clapping his hands to summon the guards. Sure enough, a band of swordsmen come pouring through an arch at the end of the landing and rush towards you. You will have to act fast.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::ARCHERY))
        {
            Choices.push_back(Choice::Base("Fight", 47));
            Choices.push_back(Choice::Base("Make a run for it", 253));
        }
    }

    int Continue(Character::Base &player) { return 230; }
};

class Story071 : public Story::Base
{
public:
    std::string PreText = "";

    Story071()
    {
        ID = 71;

        Bye = "You eventually see a swaying patch of greenery ahead and give a parched croak of joy when you realize it is the edge of the desert.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "It feels as though you have no strength left in your body. You are simply stumbling on, each step a miracle in itself. Sometimes you half faint, tumbling down a dune only to pick yourself up and somehow find the will to carry on.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_ITEMS(player, {Item::Type::WATER_BOTTLE}))
        {
            DAMAGE = -1;

            PreText += "[Item: WATER BOTTLE]";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 113; }
};

class Story072 : public Story::Base
{
public:
    std::string PreText = "";

    Story072()
    {
        ID = 72;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The guards burst into the room. You jump up onto the parapet and leap, landing with bent knees and rolling to absorb the shock of the fall. Even so, the wind is knocked out of your lungs and for a moment you lie motionless while taking stock of your injuries.\n\n";

        auto DAMAGE = -5;

        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            DAMAGE = -1;

            PreText += "[AGILITY] ";
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            DAMAGE = -1;

            PreText += "[LUCK] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nYou look up to see the guards glaring from the balcony. You drag yourself to your feet despite the pain, as it will not take them long to raise the alarm. Hobbling off towards the gate, you are met by a sentry who has heard the commotion. Peering past your shoulder, he demands: \"What's going on?\"\n\n\"A thief broke into the Caliph's bedchamber and stole his fruit bowl,\" you say, adopting a hangdog expression. \"Don't suppose I'll be getting any handouts now, what with all the fuss. Got any alms for a poor cripple, guv'nor?\"\n\nHe gives you a contemptuous glance and shoves you aside. \"Begone, you wretch,\" he cries, drawing his sword and running past you into the palace.\n\nYou smile as you watch him go. \"Thanks, I will,\" you say under your breath.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 383; }
};

class Story073 : public Story::Base
{
public:
    Story073()
    {
        ID = 73;

        Text = "The steps have been made slimy by dripping water. Your foot skids out from under you and the next moment you are plummeting through space.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            return 119;
        }
        else
        {
            return 491;
        }
    }
};

class Story074 : public Story::Base
{
public:
    Story074()
    {
        ID = 74;

        Text = "The storyteller continues, ignoring the captain's derisive scowl. ''The she-ghoul was not impressed by the prince's proposal, but her sons' pride was pricked. They insisted on proving they could outrun any mortal. ''As babes we were suckled on blood, and human flesh has always been our meat,'' they said to the prince. ''Go. You'll have five minutes' head start.''\n\nThe prince raced away, but as soon as he was out of sight of the ghouls he hid himself in a thorn bush. Soon -- much sooner than they'd promised -- the brothers came looking for him. ''He's got further than I thought,'' he heard one say. ''It's true,'' said the other, peering into the distance, ''but we'll catch him.''\n\nOnce they had run off, the prince doubled back to the hut. Now, in infancy his nurse had told him many old stories like this one. He knew that steel is of no use in killing a ghoul. Only strong wood will do the trick. He crept in to see the crone stirring the cooking-pot, and taking up a stick from beside the door he clouted her smartly -- \" The storyteller slaps his hands together, producing such a loud noise that several small children jump back in alarm.\n\nThen he grins and shakes his head sadly. \"Ah, if only he'd listened more carefully to his old nurse. For you see, he forgot that one hard blow can kill a ghoul, but a second blow will only bring it back to life stronger than before. He gave the old crone two blows for good measure -- and up she leapt, full of terrible vigour, and, seizing the prince, stuffed him into the cooking-pot.\"\n\nHe stops and looks around. \"And that is the end of the prince's tale.\"\n\n\"What drivel,\" storms the captain. \"And not even a happy ending! Come, it's time to set sail.\"\n\nYou gained the codeword CONCH.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::CONCH});
    }

    int Continue(Character::Base &player) { return 375; }
};

class Story075 : public Story::Base
{
public:
    Story075()
    {
        ID = 75;

        Image = "images/warriors.png";

        Text = "Venturing ashore, you find a flat grass-covered plain almost devoid of trees. Captain Ibrahim points out a white tower near the middle of the island. Facing it at a distance of three hundred paces or so is a large mound of white stones. \"People must have lived here once,\" infers the captain.\n\n\"Perhaps not people,\" says a voice.\n\nStartled, you whirl around to see a strange group standing just beside you. There are seven strong warriors with grey skin, whose long snouts and serried teeth make them look like sharks. In their midst is a dwarf with a rotund belly and small plump features. He wears a copper crown stamped with a mask-like face, and so tall is this crown that at first you did not realize he was a dwarf at all -- you thought the face on the crown was his real face.\n\nCaptain Ibrahim soon recovers from his surprise. \"You have a weird look about you,\" he blusters. \"I warn you not to molest us. We carry swords!\"\n\nMost of the sailors are white with fear. The dwarf smiles and says, \"Be calm. The only matter I must decide is how long you'll stay here as my guests. You see the tower there? It may interest you to know that I built it myself in a single night. Now, if you can duplicate the feat, building a second tower from that heap of white stones, I'll let you sail away in the morning.\"\n\n\"And if not?\" you ask.\n\nHe yawns as if the question is too obvious to merit an answer. With a magic gesture, he causes a large satin cushion to appear. \"I'll take a nap,\" he says, removing his crown and lying down. To the seven shark-like warriors he says: \"Do not let them depart. Wake me in the morning.\"\n\nWith that, he closes his pudgy little eyes and immediately begins to snore.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::FOLKLORE, Skill::Type::SEAFARING}))
        {
            return 283;
        }
        else
        {
            return 311;
        }
    }
};

class Story076 : public Story::Base
{
public:
    Story076()
    {
        ID = 76;

        Text = "\"At first I was amazed that any mortal could reach this city,\" says the gryphon, \"but now I see that you bear the magic bloom that allows you to walk across the clouds.\"\n\nYou glance down at the FLOWER the captain handed to you. You had forgotten you were still holding it.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::JASMINE_FLOWER});
    }

    int Continue(Character::Base &player) { return 98; }
};

class Story077 : public Story::Base
{
public:
    Story077()
    {
        ID = 77;

        Image = "images/filler1.png";

        Text = "As the echo of that ghastly whispering voice dies on the air, the cowled figures sag like puppets left to dangle on a hook. This appears to signal the end of the meeting. The islanders rise from the floor and stalk forward to bind your poor captain. He is too numb with shock to resist.\n\nYou sneak off before anyone spots you. Back at the ship, the crew listen with mounting horror as you tell your tale. \"These islanders are said to worship the corpses of their ancestors,\" mutters Sayid the helmsman. \"By heaven, it seems they are ruled by them as well.\"\n\nThe looks of fear are plain on all their faces, but one man at least has the courage to speak out on behalf of loyalty. Jumail the cook says, \"We can't leave Captain Ibrahim to die at the hands of infidels.\" He turns to you. \"If you want to try to rescue him, you can count me in.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Mount a rescue attempt", 167));
        Choices.push_back(Choice::Base("Wait for the tide and then sail at once", 258));

        Controls = Story::Controls::STANDARD;
    }
};

class Story078 : public Story::Base
{
public:
    Story078()
    {
        ID = 78;

        Text = "The captain emerges from his cabin in a sour mood and announces to the assembled crew that you will not be sailing on into the Red Sea. \"I cannot risk it,\" he says. \"Instead, we'll sell our cargo here and then return to Suhar.\"\n\nSeveral of the sailors give a groan. They had been promised a share of the voyage's profits. The rest are quite cheered by the news, since it means they will be home again sooner than they thought.\n\nYou cannot go back yet. When you set sail it was to seek adventure, and you have yet to find it. Old Madan, the ship's carpenter, sees you packing your belongings. \"So, you're disembarking here?\"\n\nYou pull the strings of your pack tight. \"What choice is there?\"\n\nHe scratches his beard and says, \"Well, I have heard tales of the Scarlet Isle to the far south. It is said to be a place of fabulous riches in gold and ivory. Why not suggest that the captain tries his luck there?\"\n\n\"Why should he listen to me?\" you ask.\n\n\"You have hidden talents. He values your opinion.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Suggest the captain sails for the Scarlet Isle", 456));
        Choices.push_back(Choice::Base("Leave and make your own way from here on", 11));

        Controls = Story::Controls::STANDARD;
    }
};

class Story079 : public Story::Base
{
public:
    Story079()
    {
        ID = 79;

        Text = "You are found, dragged from behind the bush, and thrown on your face in front of the Sultan. \"I'll slay this coward, too!\" snarls one of the knights, raising his spear.\n\n\"Hold,\" says the Sultan simply. The knight waits as though frozen, spear poised above you.\n\nYou scrabble to your feet. \"Why spare me, when you slaughtered all these others?\"\n\nPerhaps he smiles behind his mask. \"I have not spared you, only suspended your sentence of death. You intrigue me. I see with the eye that has looked on Paradise, and I see that destiny swirls about you like smoke.\"\n\nYour mind is racing. Plainly you will not get another chance.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [CUNNING]", 379, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Fight them", 17));
        Choices.push_back(Choice::Base("Make a break for it", 40));

        Controls = Story::Controls::STANDARD;
    }
};

class Story080 : public Story::Base
{
public:
    Story080()
    {
        ID = 80;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::CLOAK}))
        {
            return 35;
        }
        else
        {
            return 260;
        }
    }
};

class Story081 : public Story::Base
{
public:
    Story081()
    {
        ID = 81;

        Text = "After bidding Yussuf a tearful farewell, you make your way to the caravanserai. There you find a merchant called Hakim who is heading across the desert to Cairo. He will pay you 3 dinars to come along and guard his wares. Another merchant, by the name of Abdullah, wishes to travel east through the Peaks of the Slayers and is prepared to pay 5 dinars. The rates of pay give you an idea as to how dangerous the respective journeys are likely to be.";

        Choices.clear();
        Choices.push_back(Choice::Base("Join Hakim's expedition", 400, Choice::Type::GAIN_MONEY, 3));
        Choices.push_back(Choice::Base("Go with Abdullah", 296, Choice::Type::GAIN_MONEY, 5));

        Controls = Story::Controls::STANDARD;
    }
};

class Story082 : public Story::Base
{
public:
    std::string PreText = "";

    Story082()
    {
        ID = 82;

        Choices.clear();
        Choices.push_back(Choice::Base("Go straight ahead", 151));
        Choices.push_back(Choice::Base("Go to the left", 36));
        Choices.push_back(Choice::Base("Go to the right", 59));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The wind carries choking clouds of sand as fine as mill-dust. It clogs your throat and scours your eyes raw.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nCoughing, half-blinded, deafened by the dreary shriek of the wind -- you trudge doggedly on towards your destiny.";
        }

        Text = PreText.c_str();
    }
};

class Story083 : public Story::Base
{
public:
    std::string PreText = "";

    Story083()
    {
        ID = 83;

        Choices.clear();
        Choices.push_back(Choice::Base("Try the same tactic again", 148));
        Choices.push_back(Choice::Base("Dodge while attempting a less decisive blow", 37));
        Choices.push_back(Choice::Base("Concentrate on parrying his attacks", 60));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your blow is perfectly judged, but you may as well have struck him with a stalk of grass for all the effect it has. Laughing wildly, he dives forward and slices deep into your side.\n\nYou LOSE 4 Life Points.";

        Character::GAIN_LIFE(player, -4);

        Text = PreText.c_str();
    }
};

class Story084 : public Story::Base
{
public:
    Story084()
    {
        ID = 84;

        Text = "The mysterious island drops astern and is lost to sight. For a day or so afterwards, the captain takes to stamping around the deck fretfully. \"I should have surveyed the isle, at least,\" he admits to you. \"It might have been one of those places spoken of in the old tales.\"\n\n\"Which tales are those?\"\n\n\"You know the ones! I've heard tell of islands where the fruit is solid gold, where the streams give eternal life and the womenfolk are --\"\n\n\"Ah, I thought you meant the other tales.\" You take a sip of water from the barrel to conceal a smile. \"Stories of Sindbad's voyages -- islands inhabited by murderous cannibals, insane wizards, bloated giants and the like.\"\n\n\"Yes...\" says the captain thoughtfully. \"I expect I made the right decision, after all.\"\n\nA sailor breaks in on your conversation to point out a ship drifting ahead. Her sails are furled and there is no reply to your shouts. As you come alongside, you see the reason. The deck is strewn with corpses.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 356; }
};

class Story085 : public Story::Base
{
public:
    std::string PreText = "";

    Story085()
    {
        ID = 85;

        Bye = "You rouse yourself to see a city on the river ahead. With your last reserves of strength, you paddle your little raft to the bank and crawl ashore.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The tangled morass of waterlogged vegetation makes for hard going. You might wade for a few minutes, but there are long stretches where the only way on is to haul yourself up and climb between the trees. You are constantly plucking leeches off your legs, and more than once you hide in the treetops when you see a crocodile lazily drifting past. There is nothing you can do about the blinding swarms of insects.\n\nAt low tide you gather a few shellfish off the mangrove roots and eat them raw. After a few days you manage to collect enough wood to make a simple raft, and on this you travel swiftly until you reach a river channel. By now you are limp with fever and so thirsty that you happily lap up the stinking river water.\n\n";

        auto DAMAGE = -5;

        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            DAMAGE = -2;

            PreText += "[WILDERNESS LORE] ";
        }

        if (Character::VERIFY_ITEMS(player, {Item::Type::WATER_BOTTLE}))
        {
            DAMAGE++;

            PreText += "[Item: WATER BOTTLE] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 442; }
};

class Story086 : public Story::Base
{
public:
    Story086()
    {
        ID = 86;

        Text = "You wait until they ride into view.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::MAGIC))
        {
            return 199;
        }
        else
        {
            return -1;
        }
    }

    int Continue(Character::Base &player) { return 17; }
};

class Story087 : public Story::Base
{
public:
    Story087()
    {
        ID = 87;

        Text = "You decide to get some rest. Your opportunity to escape will come later. Pulling together a mattress of grimy straw, you doze off as the last streamers of daylight fade from the sky above the grille.\n\nYou wake up abruptly in the dead of night. A dream fades into wisps at the back of your memory. You recall being carried to the graveyard outside Baghdad. In the dream, you were alive and aware, but unable to move. Cold sweat soaks your clothing.\n\nYou reach out a hand towards your belongings. The SLIPPERS are gone! The dim moonlight lets you see well enough to tell that the old man is not here.\n\nYou notice that the old man has left his LONG-TAILED CAT behind.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::MAGIC_SLIPPERS});

        Take = {Item::LONG_TAILED_CAT};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 61; }
};

class Story088 : public Story::Base
{
public:
    Story088()
    {
        ID = 88;

        Text = "A bank of green vapour conceals you from the three sorcerers. Darting forward, you snatch up the chart they were discussing. Your eyes begin to sting, but you grope your way to one wall and climb up one of the long tapestries until you reach the balcony above. You glance down to see the sorcerers standing in the midst of the green murk. It does not have any effect on them, although you are in no doubt that it would have poisoned you in seconds.\n\nThey don't think to look up. You make your way to the end of the balcony and find a window to the outside. Climbing down, you hurry off down the hillside to safety.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::CHART});
    }

    int Continue(Character::Base &player) { return 42; }
};

class Story089 : public Story::Base
{
public:
    Story089()
    {
        ID = 89;

        Text = "Azenomei lies motionless at your feet. Slowly he begins to dissolve into a thick black miasma. A stench like burning sulphur fills the room. When his body has completely vanished, the only thing left is his SWORD.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::SWORD};

        Limit = 1;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAREM}))
        {
            return 20;
        }
        else
        {
            return 66;
        }
    }
};

class Story090 : public Story::Base
{
public:
    Story090()
    {
        ID = 90;

        Text = "You dive into the stream, forcing yourself deep under the clear cool water while the cloud of lethal hot gas rolls past overhead. At last you can hold your breath no longer. Rising with a gasp, you discover that the first wave of gas has passed. The air is filled with a reek like the fires of Hell. You hurry back down the mountain before the advancing ooze of lava cuts you off.\n\nAfter several more days of searching, you are certain that the legends are wrong. If the rokh really does exist, its nest is not in this part of the world.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try travelling to the east", 180));
        Choices.push_back(Choice::Base("Abandon the search and go home to Baghdad", 113));

        Controls = Story::Controls::STANDARD;
    }
};

class Story091 : public Story::Base
{
public:
    Story091()
    {
        ID = 91;

        Text = "You show her the fragment of diamond. \"Sorry,\" you say, abashed. \"I got this instead.\"\n\nShe looks at you as though she suspects you are a blockhead. At least she doesn't accuse you of deliberate treachery. \"Well,\" she says after drawing several deep breaths, \"at least tell my father where I am, will you?\"\n\n\"If I see him,\" you assure her. \"I don't exactly rub shoulders with the Caliph every day, you know.\"";

        Bye = "You bow and retreat from the room before she decides to turn you into a worm.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 66; }
};

class Story092 : public Story::Base
{
public:
    Story092()
    {
        ID = 92;

        Text = "You walk down by the river, where the moon's reflection lies like a sunken scimitar in the black depths. Some distance off, whispering couples glide between the trees. Blinkered by love, they take no notice of the brooding figure on the river bank.\n\nYou contemplate your future. The life of a beggar promises nothing but misery, hardship, sickness and an early death. You burn with outrage at the way Jafar treated you as beneath contempt because of your humble birth. The Caliph himself, you believe, is a good man who should be warned of his Vizier's evil plot. But an ordinary subject like yourself can hardly demand an audience with the ruler of the civilized world. It would be different if you were wealthy. \"The scales of justice are balanced by a little gold,\" as the saying goes.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go straight to the Caliph's palace", 206));
        Choices.push_back(Choice::Base("Set out in search of adventure and riches: go by sea", 160));
        Choices.push_back(Choice::Base("Join a merchant caravan heading overland", 183));

        Controls = Story::Controls::STANDARD;
    }
};

class Story093 : public Story::Base
{
public:
    Story093()
    {
        ID = 93;

        Image = "images/filler5.png";

        Text = "Tiptoeing to the further doorway, you see Jafar talking to a slave girl. You jump back out of sight just in time to avoid being seen as he turns. \"Tonight you seem radiant with satisfaction, my lord,\" purrs the slave girl, handing him a goblet of wine. \"Might it be that my company pleases you?\"\n\nJafar sneers and lifts the cup to his lips. \"You? You're a bony milk- skinned snippet I bought off a Christian. I'd get more pleasure from the company of the lice that inhabit a poor man's clothes!\" As the slave starts to weep, Jafar grins unpleasantly and says, \"I'm pleased for two reasons. The first is because today I duped a fool out of a great prize -- a stallion of unsurpassed beauty which I presented as a gift to the Caliph. Now he has given me this Robe of Honour and a palace of my own on the banks of the Tigris.\"\n\n\"And what, O mighty master, is the other reason?\" asks the slave, intrigued despite herself.\n\nYou have little hope of retrieving the stallion now that Jafar has given it to the Caliph.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay to eavesdrop on what Jafar is saying", 362));
        Choices.push_back(Choice::Base("It would be wiser to leave the palace now rather than press your luck", 183));

        Controls = Story::Controls::STANDARD;
    }
};

class Story094 : public Story::Base
{
public:
    Story094()
    {
        ID = 94;

        Text = "Sliding into the oil-black water, you swim over to the barque. As you draw level with the rail, you see a half-dozen guards crouched around a dice game on the foredeck. Inside her curtained kiosk, the woman sighs forlornly as she gazes at the moths skittering in the light of the lamps.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::STREETWISE))
        {
            Choices.push_back(Choice::Base("Show yourself to the guards", 117));
            Choices.push_back(Choice::Base("Approach the woman stealthily", 140));
        }
    }

    int Continue(Character::Base &player) { return 162; }
};

class Story095 : public Story::Base
{
public:
    std::string PreText = "";

    Story095()
    {
        ID = 95;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The guards burst into the room in time to see you lowering yourself gingerly over the balcony. Running forward, they start to shower all manner of missiles down on your head: lamps, helmets, shields, even the splintered door-frame.\n\nSomething heavy hits your shoulder. You don't see what it is, but your grip is torn from the vine and you are falling. There is a split-second of sickening terror as the air rushes past. Then you hit the ground and a jolt of pain stabs up your body.\n\nYou LOSE 6 Life Points.";

        Character::GAIN_LIFE(player, -6);

        if (player.Life > 0)
        {
            PreText += "\n\nIf you survive, you hear the guards' shouts from above. You cannot lie flopping in agony on the ground. You must rise and flee for your life before they catch you.\n\nLimping painfully towards the gate you are intercepted by a sentry. Your heart sinks, but then you realise that he does not know what the commotion is all about. He stares past you at the soldiers rushing across the courtyard. \"What's going on?\" he asks.\n\n\"There's an assassin in the palace,\" you gasp through gritted teeth.\n\nThe sentry rushes off across the courtyard. Moving with all the speed your twisted ankle will allow, you slip out of the gate and duck into the shadows of a side street. Glancing back, you see the soldiers who were chasing you run out of the gate. They look around, confused, but none saw where you went. You have given them the slip.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 383; }
};

class Story096 : public Story::Base
{
public:
    Story096()
    {
        ID = 96;

        Text = "Sparkling light appears from no obvious source. You see crystal pillars forming an alcove in the wall ahead of you. The old man whom you met on the ledge is here, dressed now in the white robes of a king of Old Persia. A black jewel shimmers at his throat. You stand in awe of the unknown as Yussuf slowly pads down the steps to join you.\n\n\"You have done well to come this far, and now you shall claim your reward,\" says the old man. \"Here are four treasures.\" He reaches into a gold-banded treasure chest and brings out a COPPER LAMP. \"This is the enchanted LAMP used by the hero Antar when he crept unseen through the harem of Sakhur the Jinni.\"\n\n\"How does it work?\" asks Yussuf.\n\n\"Merely light it, and while you hold it in your hands no-one can see you. But there is only a little of the magic oil left. Enough for a few minutes of invisibility at best.\" He puts the LAMP down and produces a coil of ROPE. \"This second treasure is a ROPE of distant India. On command it will rise straight into the air of its own accord -- a marvellous treasure for a rogue!\" He puts the ROPE aside and draws a TRUMPET out of the chest. \"And this is the HORN which levelled the walls of Jericho in ancient times. Be warned, however, that to unleash its destructive force is perilous.\"\n\nHe stands with folded arms while you gaze on the treasures. \"How many can we take?\" asks Yussuf. \"Just one?\"\n\n\"One each!\" declares the old man.\n\nYussuf leaves it to you to decide.";

        Choices.clear();
        Choices.push_back(Choice::Base("Choose the LAMP and the ROPE", 164));
        Choices.push_back(Choice::Base("Choose the ROPE and the TRUMPET", 187));
        Choices.push_back(Choice::Base("Choose the LAMP and the TRUMPET", 210));
        Choices.push_back(Choice::Base("Reject all those choices", 233));

        Controls = Story::Controls::STANDARD;
    }
};

class Story097 : public Story::Base
{
public:
    Story097()
    {
        ID = 97;

        Text = "Azenomei lunges forward, starting to utter the syllables of a new spell, but his foot catches on a rug and he stumbles. A wave of unearthly energy flows past your shoulder and crumples a bronze shield on the wall as though it were made of parchment.\n\nYou don't hang around to give him another chance. Racing pell-mell along the winding, maze-like corridors of the palace, you emerge at last in open air.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 66; }
};

class Story098 : public Story::Base
{
public:
    Story098()
    {
        ID = 98;

        Text = "The gryphon returns with you to where the ship is still stuck in the boughs of the violet-blossomed tree. The sailors loosen their swords and one man brings out a bow and arrow, but you call out to them that the creature is your friend.\n\n\"What harm can you do us now?\" says the captain in a despairing voice. \"Has your devilish sorcery not brought us enough misfortune?\" The gryphon assures him that it intends no harm. \"Let me take the mast of your vessel in my beak. I am strong enough to bear both ship and crew safely down to the waves.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Urge the captain to accept its offer of help", 121));
        Choices.push_back(Choice::Base("You think you would be better of trying a different plan", 144));

        Controls = Story::Controls::STANDARD;
    }
};

class Story099 : public Story::Base
{
public:
    Story099()
    {
        ID = 99;

        Text = "The heads of the cowled figures slump wearily to their chests. It is the signal that the meeting is over. The cowering islanders rise to their feet, and several dart forward along the room to seize Captain Ibrahim. You realize it is time to get out of here, but shock at what you've witnessed makes you hesitate just a moment too long. As you tiptoe towards the door, an islander turns and spots you. A great shriek rings out, and the others are on you in an instant.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 54; }
};

class Story100 : public Story::Base
{
public:
    Story100()
    {
        ID = 100;

        Image = "images/pirates-asleep.png";

        Text = "You give orders for the merchantman's sailors to take your ship back to port, while your own crew come aboard and man their vessel. Along with a hand-picked band of your best marines, you hide inside some empty barrels in the hold. You do not have to wait long before the cry goes out from the look-out, warning of black sails on the horizon.\n\nGrappling hooks wrench the ships together and there is the desultory clash of steel. Your sailors put up a token resistance just to prevent the pirates getting suspicious, surrendering before anyone is killed. Listening from inside the barrel, you hear the tramp of feet on the deck above. Harsh commands are given and the barrels are loaded aboard the pirate ship. The slow rolling of the heavy merchantman gives way to the swift grace of the pirates' warship.\n\nHours pass before you feel the ship jolt against the side of a dock. The pirates start to unload the barrels. You get ready to spring out on them, but then someone says, \"Let's broach this keg and have a party. We can unload the rest tomorrow.\"\n\nEven better. You wait until the noise of drunken carousing settles down into rhythmic snores, then you ease the top off your barrel and climb out. You emerge from the hold to find yourself in an underground lagoon covered by a vast stone dome. There are bronze braziers all along the shore of the lagoon, and the scene they illuminate is one of opulent luxury. The shore is covered with scattered gold, gems, ivory, pearls -- along with jars of oil and perfume, flasks of cool green wine and bolts of rich red cloth. The pirates lie asleep, limbs flung out like starfish in their wine-soaked contentment. Here you see a scar-faced villain clutching a necklace of dripping sapphires. Beside him lies a snoring red-faced ruffian hugging a blanket of lustrous silk.";

        Choices.clear();
        Choices.push_back(Choice::Base("Rely on [ROGUERY]", 12, Skill::Type::ROGUERY));
        Choices.push_back(Choice::Base("Use the LAMP of Antar", 485, {Item::LAMP_OF_ANTAR}));
        Choices.push_back(Choice::Base("You have neither of those", 58));

        Controls = Story::Controls::STANDARD;
    }
};

class Story101 : public Story::Base
{
public:
    Story101()
    {
        ID = 101;

        Text = "\"What you say is full of pragmatic wisdom,\" you say to Hakim. He nods and smiles, thinking you agree, but then you go on, \"However, it reminds me of the sad story of the man who passed Mecca every year with his camels. Each time he would pause, and bow, and say, \"Next year I will make the pilgrimage.\"\n\n\"And what happened to him?\"\n\n\"His excuses outlasted the years God had allotted to him. Whether or not he entered the gates of Paradise, I cannot say. God alone is all-knowing. But what do you think?\"\n\nHakim turns from you to the holy city with a look of concern. \"Even the most foolish of men knows the value of prudence,\" he mutters at last. \"And surely I can spare ten days of my life for He who has given me everything I possess.\"\n\nHe gives the orders for the caravan to halt.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::MORDANT}))
        {
            return 493;
        }
        else
        {
            return 146;
        }
    }
};

class Story102 : public Story::Base
{
public:
    Story102()
    {
        ID = 102;

        Text = "You give the signal. The ghoul brothers go racing off without a backward glance, chortling because they think they will soon leave you far behind. So they do, but you are not worried. Instead of racing along the path, which curves around the hillside, you climb straight up and over the ridge, dropping back onto the path before they come around the bend. The two brothers give croaks of dismay when they see your heels kicking up dust in the moonlight far in front of them. They put on a burst of desperate speed, charging like a couple of enraged bull elephants, but you still manage to just beat them back to the hut.\n\nThe old she-ghoul is dumbfounded when she learns that her sons mean to honour their agreement with you. \"Then I've been slaving away over this pot for nothing!\" she grumbles. \"Why couldn't you just cheat like your old father used to?\"\n\n\"But we lost fair and square, Ma,\" protests the elder brother, putting his hand across your shoulder. You try not to squirm. You spend the night with the ghoul family -- as bizarre a group of hosts as you've ever known. This is a story to enthral the passers-by in the bazaar in Baghdad. Unfortunately you are still no closer to fame and riches. Or are you? The next morning you bid farewell to the ghouls and set off out of the hills to join your friends.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 289; }
};

class Story103 : public Story::Base
{
public:
    Story103()
    {
        ID = 103;

        Text = "All your plotting comes to nothing. The ship sets sail the next day before you have time to formulate a plan, let alone put it into action. You are chained to the oars, and you have nothing to look forward to but the short harsh life of a galley slave. Your adventure is at an end.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story104 : public Story::Base
{
public:
    Story104()
    {
        ID = 104;

        Image = "images/filler2.png";

        Text = "The law of hospitality means that you must accept. The Bedouin would rather starve than lose face by failing to feed you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 127; }
};

class Story105 : public Story::Base
{
public:
    std::string PreText = "";

    Story105()
    {
        ID = 105;

        Choices.clear();
        Choices.push_back(Choice::Base("Enter the circle of columns", 172));
        Choices.push_back(Choice::Base("Turn away", 82));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The outline of ruins shows as a darker blot against the charcoal-coloured sky. You have arrived at a place of basalt columns that have been uncovered by the storm. You lean against them, gasping raggedly for breath in the suffocating dry dust.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou see a feeble splinter of sunlight find a crack in the swirling sand-clouds. It lasts long enough to bathe the columns in the purple colours of dream. Then the storm eclipses it again.\n\nThe place seems draped in mystery.";
        }

        Text = PreText.c_str();
    }
};

class Story106 : public Story::Base
{
public:
    Story106()
    {
        ID = 106;

        Text = "His SWORD cuts a bloody gash across your neck. Blinded for an instant by tears of pain, you fail to strike him in return.\n\nYou LOSE 2 Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Get close and attack with all your might", 148));
        Choices.push_back(Choice::Base("Make a well-aimed but weaker strike", 37));
        Choices.push_back(Choice::Base("Back away while parrying", 60));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }
};

class Story107 : public Story::Base
{
public:
    Story107()
    {
        ID = 107;

        Text = "In the dead of night, the rocking of the ship rouses you from a light doze. You have a raging thirst. As you stumble sleepily towards the freshwater barrel in the middle of the deck, you almost tread on your ship's cat. It must have been brought across by one of the others when they first explored this ship, only to get left behind in the hurry to leave. It mews piteously and rubs against your legs, so you give it a saucer of water.\n\nYou are just on the point of draining your own cup when you hear a soft thud. The ship's cat has keeled over. It wheezes a last breath and then lies still. The water... it must be poisoned! Flinging the cup away, you softly pace across the deck, giving each corpse a kick in the guts. The sixth 'corpse' you do this to gives a yelp of pain and jumps up. You have found the poisoner.\n\nHearing your shouts, the crew come across from the other ship.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 174; }
};

class Story108 : public Story::Base
{
public:
    std::string PreText = "";

    Story108()
    {
        ID = 108;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The seven warriors give barracuda grins and silently launch themselves into battle. You see the captain sliced instantly in two. Another of your companions turns to run, but one of the warriors grabs him by the shoulders and sinks his wide fang-rimmed mouth entirely around his head. A single bite ends the poor wretch's life.\n\nYou groan as you are chopped across the thighs, then sent flying by an arm that felt stronger than a swinging jib.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -4;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        if (player.Life > 0)
        {
            PreText += "\n\nIf you survive, you see that you have no chance of defeating the shark men. You cannot even save your friends. Hating yourself, but knowing you have no choice, you crawl away while the shark men are distracted by the carnage. Splashing back to the ship, you raise the anchor and let the current carry you away from the island. No one else got away. You are alone.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 266; }
};

class Story109 : public Story::Base
{
public:
    Story109()
    {
        ID = 109;

        Text = "Holding your arms out to either side, you stride along the glass column at a rapid but measured pace. Shouts from behind tell you that the Sultan and his knights have reached the brink. You ignore them. The Sultan's marvellous voice booms off the walls of the chasm, but you disregard his words. After a moment a spear whistles past your ear. You do not let it distract you.\n\nYou reach the far side. They do not dare come after you. Taunting them by bowing, you disappear into the undergrowth.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story110 : public Story::Base
{
public:
    Story110()
    {
        ID = 110;

        Text = "You can escape at any time, so there seems no need for haste. Making a mattress out of handfuls of grimy straw, you lie down to get some rest. At the top of the oubliette, beyond the grille, the last silvery gleam of daylight is fading from the sky. You yawn, dimly aware of your eyelids fluttering closed...\n\nYou wake up abruptly in a cold sweat. It is pitch dark. You were dreaming of being carried to the graveyard outside Baghdad. In the dream, you were alive but unable to move. You could not tell anyone you were still alive.\n\nYou reach out a hand towards your belongings. The INDIAN ROPE is gone! As your eyes adjust to the gloom, you see the old man is no longer beside you. He stole your ROPE and used it to escape.\n\nYou notice that the old man has left his LONG-TAILED CAT behind.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::INDIAN_ROPE});

        Take = {Item::LONG_TAILED_CAT};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 61; }
};

class Story111 : public Story::Base
{
public:
    Story111()
    {
        ID = 111;

        Text = "A rope drops from the balcony above and a figure comes sliding down to land beside you. It is Azenomei. \"Put this across your mouth,\" he urges, handing you a piece of silk soaked in vinegar.\n\nYou are in no position to argue. While you wind the silk around your face, Azenomei daringly rushes forward into the bank of green fog. One of the sorcerers tries to grab him, but only gets a hard buffet across the chin for his trouble. Snatching up the CHART, Azenomei throws it to you and then leads the way back up the rope to the balcony. At the end is a window, and another rope takes you to safety outside the citadel.\n\n\"You see,\" says Azenomei as the two of you race off down the hillside, \"you do need me.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Agree to help Azenomei rescue his sister", 270));
        Choices.push_back(Choice::Base("Refuse to accompany him across the desert", 179));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::NOOSE);

        Take = {Item::CHART};

        Limit = 1;
    }
};

class Story112 : public Story::Base
{
public:
    std::string PreText = "";

    Story112()
    {
        ID = 112;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Azenomei's golden eyes flash with eagerness for the kill. Pulling his sword from his belt, he leaps forward to match you blow for blow. Both of you suffer dreadful wounds, and red human blood soon mingles underfoot with the black ichor of jinni's veins. You feel yourself weakening, but you are determined to make this a fight to the bitter end.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -4;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 89; }
};

class Story113 : public Story::Base
{
public:
    Story113()
    {
        ID = 113;

        Text = "Falling in with a group of travellers, you return at last to Baghdad.\n\nYou RECOVER 4 Life Points.\n\nAlmost a year has passed since you left, and a lot has changed in that time. Soldiers patrol the streets and a curfew forces everyone off the streets after evening prayers. The City of Peace has become a city of fear. Whenever you ask the reason, people compress their lips and warn you to keep silent, until finally a blind old woman tells you: \"The Caliph believes the city is on the brink of revolt.\"\n\n\"And is it?\"\n\nShe shakes her head. \"Not to start with -- but the more he tightens his grip, the more likely it becomes.\"\n\n\"This is Jafar's doing.\"\n\n\"Perhaps.\" She tilts her head at the sound of the muezzin's echoing chant. \"The curfew. I must find a place to shelter for the night.\"\n\nAs she hobbles off, you consider your options.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 4);

        Choices.clear();

        if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::ZEBRA}))
        {
            Choices.push_back(Choice::Base("Use the LAMP of Antar", 45, {Item::LAMP_OF_ANTAR}));
            Choices.push_back(Choice::Base("Use a DIAMOND", 194, {Item::DIAMOND}));
            Choices.push_back(Choice::Base("Otherwise", 251));
        }
    }

    int Continue(Character::Base &player) { return 205; }
};

class Story114 : public Story::Base
{
public:
    Story114()
    {
        ID = 114;

        Text = "Ayisha first casts a spell of healing.\n\nYour Life Points are restore to their original score.\n\nShe follows this with another, more powerful enchantment. A dark whirlwind springs up around you. You feel yourself being flung across vast distances. For a moment you taste rain, and see the flash of lightning behind a leaden cloud. Then there is sun on your face, and you are dropping towards a verdant island set in a sparkling blue sea.\n\nYou land with a thump and the whirlwind swirls away. Picking yourself up, you look around. You are beside a sheer pinnacle of rock that rises from the centre of the island. You cannot see the top because of the clouds above.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.Life = player.MAX_LIFE_LIMIT;
    }

    int Continue(Character::Base &player) { return 136; }
};

class Story115 : public Story::Base
{
public:
    Story115()
    {
        ID = 115;

        Image = "images/filler5.png";

        Text = "The astrologer leads you up a winding staircase to a tower room at the top of his house. An archway opens onto the night, giving a crystal-clear view of the sky. While you settle yourself down on a pile of velvet cushions, he brings a wooden table on which he sets up a brass astrolabe. For several minutes he takes sightings of the stars, every so often giving a grunt and jotting something down on the chart at his elbow. At last he turns and says, \"I see a thief among thieves, a most daring knave, bold and lucky as an alley cat.\"\n\n\"Is it me? Or is this someone I shall meet? Where will it happen?\"\n\nHe holds up a hand to stem your flood of questions. \"The future is like a page from a book seen in a dream. The words are not written in the clearest hand, nor in the sharpest of inks. All I know is that a great journey lies ahead. Beware, then, as a journey can mean death! Treachery awaits you with a plain mark on his face. Sages and sorcerers may help or hinder you. In a place of many doors you will find your destiny...\"\n\nHis voice trails off. In a less ominous tone he adds, \"These things I have described are but the myriad possibilities of your future. You stand as at a crossroads. Choose your destiny.\"\n\nThanking him, you leave more baffled than when you came in.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 92; }
};

class Story116 : public Story::Base
{
public:
    Story116()
    {
        ID = 116;

        Text = "Masrur's SWORD slices the air, only to catch in the drapes just above your head. There is a ripping of velvet fabric as he yanks it free and stares around. But by this time you have already dodged past and run to the doorway.\n\nUttering a scornful oath, Jafar pushes the burly warrior aside and takes a step forward. \"Guards!\" he yells as he claps his hands imperiously. \"Guards! A thief is at large in the palace!\"\n\nYou turn your head in time to see a band of swordsmen come rushing towards you through an arch at the end of the landing. You will have to act fast.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::ARCHERY))
        {
            Choices.push_back(Choice::Base("Fight", 47));
            Choices.push_back(Choice::Base("Make a run for it", 253));
        }
    }

    int Continue(Character::Base &player) { return 230; }
};

class Story117 : public Story::Base
{
public:
    Story117()
    {
        ID = 117;

        Text = "You seize the rail and haul yourself dripping onto the deck. The guards leap up with angry expressions. Lamplight flares on naked steel as they draw their swords. \"Begone!\" cries the nearest guard. \"We'll slay anyone who tries to take the lady from us.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Meekly return to your own ship", 375));
        Choices.push_back(Choice::Base("Decide to fight", 185));

        Controls = Story::Controls::STANDARD;
    }
};

class Story118 : public Story::Base
{
public:
    Story118()
    {
        ID = 118;

        Text = "You turn to run, but behind you there is only a slab of unyielding rock. You join Yussuf in hammering against it, shouting for help as the monstrous horde draws closer. Their noxious breath makes you choke. Turning, you look straight into the pitiless cyclopean faces.\n\nA taloned limb rises, throwing a jag-edged shadow on the cave roof.\n\nYou open your mouth to scream.\n\nThe talon falls, silencing you for ever.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story119 : public Story::Base
{
public:
    Story119()
    {
        ID = 119;

        Image = "images/filler2.png";

        Text = "You drop only a few feet, hitting the floor of the cavern with a painful thud. You were almost at the bottom of the staircase already, only you didn't realise it. You will have a nasty bruise to show for it, but at least you are alive -- for now.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 96; }
};

class Story120 : public Story::Base
{
public:
    Story120()
    {
        ID = 120;

        Text = "The Caliph lavishes gifts on you: gold, jewels and splendid robes of honour. \"This is not all,\" he says. \"Now I need a new Grand Vizier.\"\n\n\"Me, lord?\" You bow to keep him from seeing the look of shock on your face. \"But I am not wise or worthy enough.\"\n\nHe laughs. \"What you mean to say is, you're not a fat, spoiled court popinjay.\"\n\n\"Prince of Princes, I would never say such -- \"\n\n\"Then you are diplomatic enough for the job. Also, you have proved wise where it matters, which is not in academic affairs but in affairs of the human heart. Moreover, you have seen much of the world. I shall enjoy hearing your tales.\"\n\nAnd so, from humble origins, you suddenly find yourself the Grand Vizier to the Caliph of Baghdad. You are rich and respected. Nobles and courtiers flock to hear your advice. The Prophet warned against intoxication, but you had always thought that referred only to wine. Now you know that destiny, too, can be a heady draught.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 496; }
};

class Story121 : public Story::Base
{
public:
    Story121()
    {
        ID = 121;

        Text = "The gryphon is as good as its word. Beating its wings with hurricane force, it pulls the ship clear of the branches and swoops down, bearing you off the edge of the cloud and down towards the azure water far below.\n\n\"By the blessed Creator of All!\" gasps Captain Ibrahim, his face as white as the fluttering sails. \"This is no voyage for a sailor.\"\n\n\"Cheer up,\" you tell him. \"When you return to Baghdad, this will be a tale to match any that has ever been told.\"\n\nAs the ship touches the waves, his look of drawn horror slowly gives way to a broad smile. \"That's true...\"\n\nThe gryphon circles once and soars off into the sky. As one man, the crew fall to their knees and bow towards Mecca, thanking God for their safe deliverance.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 234; }
};

class Story122 : public Story::Base
{
public:
    std::string PreText = "";

    Story122()
    {
        ID = 122;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Grabbing the rafters, you swing yourself up and drive a hard kick into the midriff of the man right in front of you. He goes flailing back and collides with Captain Ibrahim, who gives him a hefty clout across the chin and snatches up his sword. Ibrahim's bewildered expression gives way to a joyous lusty roar as he leaps forward to help you.\n\nStanding back to back, the two of you fight your way to the door.\n\n";

        auto DAMAGE = -4;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -1;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nYou still have breath in your body, you race off with the islanders in close pursuit.\n\nThe jetty comes in sight. Encouraged by the crew's yells, you ignore the stones and spears that are whistling past your heads. Leaping aboard, the captain gives the immediate order to cast off. The ship lurches out from the jetty and swirls on the river currents. You watch from the rail as the angry mob comes charging onto the jetty. Some career into the water in their haste, and now it is the turn of your crew to pelt them with missiles.\n\nAs he gets his breath back, Captain Ibrahim tells you that the islanders kept asking him about the nest of the rokh, the giant bird said to prey on elephants. \"I told them I wanted only to trade, but they were having none of it,\" he pants. \"They accused me of being after the rokh's diamond eggs.\"\n\n\"Its nest must be somewhere in these parts, then.\"\n\n\"They said it was somewhere to the west,\" he says with as much interest as if he were speaking about the shape of a bee's backside. \"But I think it's just so much poppycock.\"\n\nYou gained the codeword KISMET.";

            Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 346; }
};

class Story123 : public Story::Base
{
public:
    Story123()
    {
        ID = 123;

        Image = "images/filler3.png";

        Text = "You journey on for several days. The road turns away from the coast and rises towards some hills which present an outline of dull grey- brown against the clear indigo hues of the sky. Hakim eyes the pass through the hills with a worried frown. He fears an ambush by bandits.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::MORDANT}))
        {
            return 191;
        }
        else
        {
            return 214;
        }
    }
};

class Story124 : public Story::Base
{
public:
    Story124()
    {
        ID = 124;

        Text = "One of the ghoul brothers gives the signal and they go charging off down the path like a pair of stampeding elephants. You stand watching them in the moonlight. After fifty metres or so, one of them glances back and laughs, saying, \"Haw! You forgot to start at the signal. You don't have a chance of catching us now!\"\n\n\"You're right,\" you reply, \"I don't.\" And you shoot him through the heart.\n\nThe other ghoul skids to a halt, stares at his brother's corpse in shock, then glowers at you. He takes a step back along the trail, sees you nocking another arrow, and starts to back away.\n\nYou release the second arrow and watch it streak to find its mark. You give a sad shake of the head as you turn away. They were almost too easy. Now to deal with the vile monster that spawned them.\n\nShe looks up from tasting a ladle of stew as you kick the door in. Her slack blue-lipped mouth starts to frame a quizzical frown. The expression turns to a death grimace as your arrow splits her throat. Stepping over the body, you make a quick search of the hut, finding 15 dinars in a jar.\n\nYou also take a warm woollen CLOAK. You have no desire to spend the night here, and you will need something to keep warm while sheltering amid the rocks. The CLOAK is crawling with lice, but you hold it over the fire for a few minutes so that the smoke drives most of them out.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 15);

        Take = {Item::CLOAK};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 80; }
};

class Story125 : public Story::Base
{
public:
    Story125()
    {
        ID = 125;

        Image = "images/masked-rider.png";

        Text = "The four riders are garbed all in white, with silver filigree around the borders of their robes. Three look down with fierce eyes. The emotions of the fourth remain a mystery, for he wears a mask of carved ivory. All carry bristling lances. Knives and long swords hang at their belts.\n\nThe masked rider points to the fallen gazelle. \"This was our game, which we'd pursued since before sunrise. You've stolen it.\" His voice sounds as sweet as the melody of a harp, as sweet as a fresh brook, as sweet as poisoned syrup.\n\nAbdullah becomes truculent. \"Who are you, to lay such accusations on us?\"\n\nThe masked stranger leans forward in his saddle. \"I am the Sultan of Nishapur.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 378;
        }
        else
        {
            return 398;
        }
    }
};

class Story126 : public Story::Base
{
public:
    std::string PreText = "";

    Story126()
    {
        ID = 126;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "He casts another spell as you flee.";

        if (!Character::VERIFY_ITEMS(player, {Item::Type::BLACK_JEWEL}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nThe spell takes effect and you are aged a hundred years in the space of a single heartbeat, falling to gasp your last feeble breaths on the cold hard floor.";
        }
        else
        {
            PreText += "\n\nThe BLACK JEWEL absorbs the spell into itself, crumbling to powder as it does";

            Character::LOSE_ITEMS(player, {Item::Type::BLACK_JEWEL});
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 66; }
};

class Story127 : public Story::Base
{
public:
    Story127()
    {
        ID = 127;

        Text = "The meagre meal is surprisingly good. The Bedouin watch with empty stomachs as you enjoy the only food they have to spare. The children of the tribe begin to cry, so the chief starts a song to distract them from their hunger. The meal over, you recline on soft cushions. Night rushes across the sky, unfolding a multitude of stars while the stirring strains of the desert song resound off the looming dunes around you.\n\nHakim makes a gift of salt to the tribe. The chief tries to hide his almost pathetic gratitude at this kindness. \"Beware when you cross the desert,\" he warns you. \"The tribes of the remote interior show no shame in stealing from others.\"\n\nThanking the Bedouin for their hospitality, you spend the night with them and head on at first light.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            return 168;
        }
        else
        {
            return 217;
        }
    }
};

class Story128 : public Story::Base
{
public:
    Story128()
    {
        ID = 128;

        Text = "You stumble into a patch of quicksand. As it sucks you down, you twist around and try to pull yourself out using the halter of the camel you were leading. But the camel tugs away in fright, jerking the halter out of your hand. You see the horror-stricken looks on your companions' faces as they watch you sink inexorably into the ground. Hakim calls out something, but you cannot hear him over the howl of the storm. Then the quicksand closes over your head and you are plunged into silence and darkness.\n\nYou drift weightlessly down. Your pulse pounds in your ears and your chest is close to bursting, but you cannot bring yourself to give up your last breath. Just as it seems the cloud of oblivion is descending across your mind for ever, you fall out of the fluid sand and into an underground chamber.\n\nYou have never been so grateful for the simple taste of fresh air. Falling on your face, you give thanks to God for sparing you. But then you hear a voice that makes every muscle shake with fear.\n\n\"I am the only god here,\" it says.\n\nYou look up.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 25; }
};

class Story129 : public Story::Base
{
public:
    Story129()
    {
        ID = 129;

        Text = "Falling into an easy rhythm, you manage to sweep blow after blow aside, parrying as though in a trance. A mystical sense of tranquillity comes over you. You seem to be sunk in a dream. The sight of your foe's glaring gaze no longer fills you with terror. The scene is one of unearthly beauty -- the shimmering colours of the silk tapestries, like streams of spring water... the heady odour of perfume and incense... the lustrous sheen of gold and jewels...";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 152; }
};

class Story130 : public Story::Base
{
public:
    Story130()
    {
        ID = 130;

        Text = "Only poison could have killed these people so quickly. The obvious source would have to be the freshwater barrel in the middle of the deck. It might have become tainted by accident, but you doubt it. More likely that one of these bodies lying around the vessel is rather friskier than anyone suspects.\n\nThere is an easy way to find out. You pretend to take a drink of water and then fall back limp on the deck. Watching with squinted eyes, you see one of the 'corpses' rise to its feet and creep over to search your belongings. Giving vent to a fierce yell that would curdle the blood of a cannibal, you leap up and seize the crafty poisoner.\n\nJubilantly you hail your fellow sailors on the other ship, telling them to come across at once.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 174; }
};

class Story131 : public Story::Base
{
public:
    Story131()
    {
        ID = 131;

        Text = "The ship is tossed far out to sea. You can hardly see the others through the deluge of black bone-chilling rain. You hear a scream, drowned out by the storm's roar, as the helmsman is pinned against the rail and crushed by the tiller.\"She's breaking apart!\" you hear someone screech as the mainmast splits and falls ponderously like a great tree. It brings the ragged sails with it. You are flung back as the ship gives a lurch, plunged into water which seems strangely warm after the icy rails of rain. It is like being submerged in blood. The muffled sounds of the undersea thunder in your ears. Your fingers find a plank of broken wood. You break to the surface with a gasp and look around, but there is nothing to see but the crashing waves. The ship has gone.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 280; }
};

class Story132 : public Story::Base
{
public:
    Story132()
    {
        ID = 132;

        Text = "Tapping the glass column, you discover it is hollow. Perhaps a bizarre aqueduct left by an ancient civilization? You dig madly at the earth of the bank into which it is set until you clear a space large enough to squeeze through. Inside the pipe, suspended above a dizzying drop, you crawl on hands and knees to the far end, where you dig up to the surface.\n\nYou look back to see the Sultan and his horsemen milling about on the lip of the chasm. They saw how you got across, but cannot follow for fear of being picked off as they emerge.\n\nThe Sultan's laughter rolls like a waterfall off the high rocks. \"Clever rogue, you've won your freedom. Return, and I'll reward you for amusing me.\"\n\n\"Keep your reward, I prefer a long life,\" you reply before turning and vanishing into the undergrowth.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story133 : public Story::Base
{
public:
    Story133()
    {
        ID = 133;

        Text = "When everyone is asleep, you ascend to the grille. It is fastened shut by a large bronze padlock.";

        Choices.clear();
        Choices.push_back(Choice::Base("[ROGUERY] Pick the lock", 178, Skill::Type::ROGUERY));
        Choices.push_back(Choice::Base("Try using [MAGIC]", 246, Skill::Type::MAGIC));
        Choices.push_back(Choice::Base("Try using a HAWK", 201, {Item::HAWK}));
        Choices.push_back(Choice::Base("You may as well give up any thought of escaping for now", 155));

        Controls = Story::Controls::STANDARD;
    }
};

class Story134 : public Story::Base
{
public:
    std::string PreText = "";

    Story134()
    {
        ID = 134;

        Choices.clear();
        Choices.push_back(Choice::Base("Use [CUNNING]", 65, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Try using [AGILITY]", 88, Skill::Type::AGILITY));
        Choices.push_back(Choice::Base("Try using a BLACK JEWEL", 156, {Item::BLACK_JEWEL}));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "The cloud of poisonous fog spreads rapidly to fill the room.";

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::CUNNING, Skill::Type::AGILITY}) && !Character::VERIFY_ITEMS(player, {Item::Type::BLACK_JEWEL}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nThe smoke envelops you and you fall senseless to the floor, never to recover.";
        }

        Text = PreText.c_str();
    }
};

class Story135 : public Story::Base
{
public:
    Story135()
    {
        ID = 135;

        Text = "You ask him the cause of his sorrow. \"Is it because you lost your hand?\" He nods, still weeping. \"What irony! What a vicious twist of fate! I am Shazir, and only a week ago I was the greatest thief in the world. Jafar of Baghdad hired me to steal a fragment of the rokh's diamond egg for him.\"\n\n\"What happened?\" you ask. \"Did the rokh bite off your hand?\" He gives a bitter scowl. \"I never got that far. The first stage was to acquire a boat, so I came to this very village, which is the place where I was born. It amused me to think that here was I, the renowned Shazir, returning to the village where I had last been seen fifteen years ago. When I left I was just a scrawny young ragamuffin with a mop of unruly hair, so how could I imagine anyone would recognize me?\"\n\n\"But someone did?\"\n\n\"Old Muluk, from whom I once stole two fishes,\" replies Shazir, nodding. \"He had me seized, they summoned the local judge, and my hand was cut off. Oh, to cut off my hand just for two fishes! I, who have stolen from the treasuries of kings!\"\n\n\"Certainly the loss of your hand will handicap your illustrious career.\"\n\n\"More than that: my life is forfeit! I have already spent the money Jafar gave me. When I fail to turn up with the eggshell, he'll have his spies hunt me down.\"\n\n\"Possibly not.\" His story has given you an idea. \"Why not swap clothes with me? I'll sail off and get the eggshell and take it to Jafar, pretending to be you.\"\n\nShazir shakes his head. \"Absurd. You look nothing like me.\"\n\n\"In dim light I might pass. If he questions me, I'll say I'm your cousin.\" Seeing Shazir hesitate, you add, \"Isn't it better than certain death?\"\n\nFinally he agrees. He gives you his clothes and introduces you to the fishermen who were going to take him to the rokh's island.\n\nYou gained the codeword ZEBRA.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::ZEBRA});
    }

    int Continue(Character::Base &player) { return 203; }
};

class Story136 : public Story::Base
{
public:
    Story136()
    {
        ID = 136;

        Text = "As you stand gazing up the daunting pinnacle, a great black blot comes dropping through the cloud towards you. At first you feel a stab of terror because you think it is a dislodged boulder. You step back, fearing you'll be crushed, but then the shape opens its wings and goes swooping out across the island.\n\nYou can only stand dumbstruck. It is the rokh. None of the tales prepared you for the true sight of it: a great soaring raptor whose shrieks rattle the rocks around you, and whose claws are big enough to carry off an elephant.\n\nThe rokh settles on a sheep, pressing the terrified animal down with a lazy sweep of its talons. One peck is enough to end the sheep's life. The bloody flesh drips from the rokh's beak -- no more than a morsel for such a giant creature.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::ROGUERY) && !Character::VERIFY_ITEMS(player, {Item::Type::LAMP_OF_ANTAR}))
        {
            Choices.push_back(Choice::Base("Start to climb", 181));
            Choices.push_back(Choice::Base("Look through your possessions", 204));
            Choices.push_back(Choice::Base("The sight of the rokh has given you second thoughts: you are ready to give up and go home", 142));
        }
    }

    int Continue(Character::Base &player) { return 158; }
};

class Story137 : public Story::Base
{
public:
    Story137()
    {
        ID = 137;

        Text = "Consider the following points in turn.";

        Choices.clear();
        Choices.push_back(Choice::Base("You have a CHART", 203, {Item::CHART}));
        Choices.push_back(Choice::Base("You have the codeword FABRIC", 203, {Codeword::Type::FABRIC}));
        Choices.push_back(Choice::Base("Try using [FOLKLORE]", 226, Skill::Type::FOLKLORE));
        Choices.push_back(Choice::Base("Try using [SEAFARING]", 226, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("You have the codeword KISMET", 271, {Codeword::Type::KISMET}));
        Choices.push_back(Choice::Base("You have none of those", 248));

        Controls = Story::Controls::STANDARD;
    }
};

class Story138 : public Story::Base
{
public:
    Story138()
    {
        ID = 138;

        Text = "The sailor speaks with rapture of the joys of seafaring. \"The salt spray has a scent more lovely than the spices of Ceylon,\" he says. \"And what jewel ever shone as bright as the setting sun, smouldering like a ruby above the languid gold of the ocean?\"\n\nAs you approach the docks, however, his mood becomes more practical. \"You'll first sail downriver to Basra,\" he says. \"From Basra on to the open sea of the Gulf. Once past the Straits of Hormuz, I'd counsel you to stay close to shore if you wish to avoid a hazardous adventure. Somewhere in the Indian Ocean lies the island of a malevolent dwarf. He has deep knowledge of dire sorcery. It's said that he does not welcome visitors, but nor does he hurry to see them leave again once they've found his isle. His seven sentinels have as much mercy as sharks.\"\n\nYou nod, glancing away to hide your sceptical smile. \"I'm grateful for this advice. Are there other dangers of the deep I should watch out for?\"\n\nHe spreads his hands as if at an embarrassment of riches. \"The giant fish called the dendan, which swallows ships. The people of the Scarlet Isle, who are ruled by dead kings. The evil fire wizards whom the Prophet cast out from this land two centuries ago. And sundry ghosts, ifrits and cannibal pirates, of course...\"\n\nYou raise your eyebrows. \"Are you sure that going to sea is a good idea?\"\n\n\"Now I come to think,\" says the sailor, pulling thoughtfully at his beard, \"it is a perilous life at best. But consider the great rewards, my friend, if you should survive to reach one of those fabulous ports where silks and spices are as plentiful as the plums of the Caliph's garden.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("You are resolved to seek adventure at sea", 160));
        Choices.push_back(Choice::Base("You think it would be better to join a merchant expedition heading overland", 183));

        Controls = Story::Controls::STANDARD;
    }
};

class Story139 : public Story::Base
{
public:
    Story139()
    {
        ID = 139;

        Image = "images/filler2.png";

        Text = "Pulling off the HAWK's hood, you thrust the bird into Masrur's face. It is just as surprised as he is, beating the air with its wings and thrusting its talons out by instinct. You see a livid red weal appear across\n\nMasrur's heavy jowels and he flings his sword aside, clutching at the painful gash. The HAWK flutters over to settle on Jafar's arm.\n\nYou run back to the doorway. But the Palace guards have heard the commotion, and even now a band of swordsmen are rushing at you from one end of the landing. Glancing back, you see Jafar stroll unhurriedly forward with a look of triumph on his pudgy face.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::HAWK});

        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::ARCHERY))
        {
            Choices.push_back(Choice::Base("Stand your ground and fight", 47));
            Choices.push_back(Choice::Base("Run for your life", 253));
        }
    }

    int Continue(Character::Base &player) { return 230; }
};

class Story140 : public Story::Base
{
public:
    Story140()
    {
        ID = 140;

        Text = "Moving noiselessly between the softly swaying drapes, you put your finger to the woman's lips. Though startled, she nods to signal that she will not cry out for the guards.\n\n\"Who are you?\" she whispers. \"Have you come to answer my prayers? To rescue me from my fate?\"\n\n\"What fate is that?\" you reply quietly, keeping one eye on the hunched silhouettes of the guards at the front of the barque.\n\n\"I was the Caliph's slave, but I displeased his vizier, who arranged to have me sent as a gift to the Governor of Basra. I would sooner die than join his harem.\"\n\n\"I too have a grudge against Jafar.\"\n\n\"Then help me escape. When I do not arrive in Basra, Jafar himself will have to pay for another concubine.\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (player.Gender != Character::Gender::FEMALE)
        {
            Choices.push_back(Choice::Base("Leap out and attack the guards", 320));
            Choices.push_back(Choice::Base("Use [CUNNING]", 342, Skill::Type::CUNNING));
            Choices.push_back(Choice::Base("[MAGIC] Summon a jinni", 364, Skill::Type::MAGIC));
            Choices.push_back(Choice::Base("Return to your ship: you prefer not to get involved", 375));
        }
    }

    int Continue(Character::Base &player) { return 298; }
};

class Story141 : public Story::Base
{
public:
    std::string PreText = "";

    Story141()
    {
        ID = 141;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "Pushing Yussuf back, you launch yourself into the thick of the devilish horde with a defiant cry of battle-fury. Chittering madly, they rip at your flesh with their hard axe-like talons and razor-edged jaws. One reaches past you for your cringing friend, who fends it away with a feeble blow and then falls to his knees and buries his head in his hands.\n\nYou have no time to worry about Yussuf. You push one of the monsters away, but another closes its jaws on your wrist and you feel the crunch of sinew as your blood spurts across its moist leathery orb of an eye.";

        if (!Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}) && !Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nWithout combat skills you have no hope at all, and you go down fighting under a hail of blows.";
        }
        else
        {
            PreText += "\n\n";

            if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
            {
                PreText += "[SWORDPLAY] ";
            }

            if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
            {
                PreText += "[WRESTLING] ";
            }

            Character::GAIN_LIFE(player, -6);

            PreText += "You LOSE 6 Life Points.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 209; }
};

class Story142 : public Story::Base
{
public:
    Story142()
    {
        ID = 142;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAREM}))
        {
            return 159;
        }
        else
        {
            return 113;
        }
    }
};

class Story143 : public Story::Base
{
public:
    Story143()
    {
        ID = 143;

        Text = "Choose what to do next.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use a PRAYER-MAT now", 165, {Item::PRAYER_MAT}));
        Choices.push_back(Choice::Base("[MAGIC] Summon a jinni", 188, Skill::Type::MAGIC));
        Choices.push_back(Choice::Base("Otherwise", 211));

        Controls = Story::Controls::STANDARD;
    }
};

class Story144 : public Story::Base
{
public:
    Story144()
    {
        ID = 144;

        Text = "The captain orders the rigging stripped and spliced together, making a long rope which is lowered over the edge of the cloud.\n\n\"As the cause of all this trouble, you shall go first,\" he says.\n\nWeak with fear, you slither down the rope. When you reach the bottom there is still a drop of forty feet to the sea. You let go and fall, hitting the water with stunning force. Drenching darkness closes over your head.\n\nYou LOSE 1 Life Point.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 280; }
};

class Story145 : public Story::Base
{
public:
    Story145()
    {
        ID = 145;

        Text = "Racing through the streets back to the ship, you scramble aboard and gasp out the order to cast off. As the ship pulls away from the dock, you raise yourself breathlessly and lean on the rail to watch a mob of angry islanders come chasing after you. They are too late. The front runners race to the edge of the jetty intending to jump aboard, but they see the distance is too far and stand suspended with flailing arms and comical alarmed stares before plunging over into the water. Your relief at escaping from such peril spills over into laughter, and the rest of the crew join in.\n\nSuddenly a grim old man pushes through the throng. Something about the look of him chokes off your merriment. He raises a staff topped by a human skull and begins a low howling chant that reverberates off the hills. You feel a prickling in the hair of your scalp. You are sure it is a curse.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::MAGIC))
        {
            return 324;
        }
        else
        {
            return 346;
        }
    }
};

class Story146 : public Story::Base
{
public:
    Story146()
    {
        ID = 146;

        Text = "This is no carefree jaunt for the half-hearted. The rituals are rigorous and take many days. First you visit the Great Mosque, where the looming black block of the sacred Kaaba stands like the very fingerprint of God against the sky. Circling this seven times, as tradition demands, is wearying in the intense desert heat. You are soon soaked in sweat and coughing because of the dust thrown up by hundreds of feet.\n\nAfter kissing the black stone, you drink and wash in the sacred well, Zamzam. Then there is an arduous run to and fro between two mountains just outside the city walls. You see an old man falter and drop to his knees. By now you are suffused with understanding of the Prophet's teachings and you stop to help him even though you, too, are close to fainting.\n\nYour kindness is repaid. The old man helps you with your prayers in the days that follow. On the eighth day, you listen to a sermon preached at the same spot where the Prophet last spoke to his people in this life. Then, as the sun pulls streamers of red fire out of the sky to the west, you must walk to the Pillars of Mena where you spend the next day collecting pebbles. When you wonder at the meaning of this, the old man is on hand to instruct you. It seems that when Ismail was tempted by the Devil to disobey his father, Abraham, he drove the Devil away by throwing stones at him.\n\nOn the last day you sacrifice a sheep and distribute the meat to the poor. This symbolizes the sheep that Abraham sacrificed to God in place of his son Ismail.\n\nThe rituals are over. You are now a hajji, a pilgrim, and may wear a green turban to show this.\n\nYou gained the codeword HAJJI.";

        Bye = "The next morning you awaken invigorated after your first good restful sleep in many days.\n\nYou RECOVER 2 Life Points.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::HAJJI});

        Character::GAIN_LIFE(player, 2);
    }

    int Continue(Character::Base &player) { return 123; }
};

class Story147 : public Story::Base
{
public:
    std::string PreText = "";

    Story147()
    {
        ID = 147;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The two ghouls race off ahead and are soon out of sight. Gasping for breath, you realize you cannot hope to keep up with them. No doubt they have benefitted from their high-protein diet. You decide that it would be better to simply slink away. You are clambering down through the rocks when you hear an ominous cough just behind you. Whirling, your heart sinks to see the ghoulish witch and her sons standing right behind you. She is holding a divining rod which she points towards you, saying through gritted teeth: \"There's your supper. Don't lose it again.\"\n\nThey club you brutally to the ground.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        Choices.clear();

        if (player.Life > 0)
        {
            PreText += "\n\nYou are gripped firmly by the arms and led back to the hut. As they shove you inside, the mother starts looking at the jars along the shelves. \"Let's see... a bit of pepper and some garlic ought to set off the flavours nicely.\"\n\nYou must do something.";

            if (!Character::VERIFY_SKILL(player, Skill::Type::MAGIC))
            {
                Choices.push_back(Choice::Base("Go down fighting", 370));
                Choices.push_back(Choice::Base("Otherwise", 305));
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 327; }
};

class Story148 : public Story::Base
{
public:
    std::string PreText = "";

    Story148()
    {
        ID = 148;

        Choices.clear();
        Choices.push_back(Choice::Base("Try the same tactic again", 83));
        Choices.push_back(Choice::Base("Weave back and go for a lighter blow", 37));
        Choices.push_back(Choice::Base("Try to parry", 60));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You cut him deeply across the chest, but his skin is hard like wind- dried leather and he only smiles at your efforts. Striking back, he inflicts a wicked gash to your thigh.\n\nYou LOSE 4 Life Points.";

        Character::GAIN_LIFE(player, -4);

        if (player.Life > 0)
        {
            PreText += "\n\nYou are still able to fight.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 327; }
};

class Story149 : public Story::Base
{
public:
    Story149()
    {
        ID = 149;

        Image = "images/filler3.png";

        Text = "The streets of the city are tiered thoroughfares that snake up between the clustered houses to the palace at the top of the hill. As you ascend the steps of one such street, you are shouldered aside by a patrol of stern-faced soldiers. Affronted at their rudeness, you give them a glowering look as they descend towards the docks.\n\nA passing barber notices the incident and says to you: \"The palace guards are looking for a thief who stole a ruby from the treasury. The Sultan is furious, and he has decreed that if the thief is not caught by the time the moon rises tonight, the captain of the palace guard will be crucified.\"\n\nYour pride is still ruffled. \"I can understand their urgency, then. All the same, there is no excuse for manhandling an honest traveller in that way.\"\n\nHe peers at you in the dusk. \"Ah, you are a stranger to the city?\"\n\n\"Yes,\" you say, nodding. \"What of it?\"\n\nHe suddenly leaps back and cries: \"Here is the thief! Here!\"\n\nBefore you can react, the soldiers turn and race back up the street.\n\nAs you start to raise your hands, the barber leaps on your back, bearing you to the ground.\n\nThe soldiers grab you. \"Well done, friend,\" their officer says to the barber. \"You'll be rewarded for this.\"\n\n\"My reward awaits me in heaven,\" he says.\n\n\"I'll give it to you myself,\" you growl at him, \"once I've explained there's been a mistake.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 250; }
};

class Story150 : public Story::Base
{
public:
    Story150()
    {
        ID = 150;

        Image = "images/sorcerers.png";

        Text = "You draw back further out of sight, but in your anxiety to avoid being spotted you fail to notice a shield fixed to the wall behind you. It falls with a clang. The three sorcerers whirl.\n\n\"Stop!\" cries the leader.\n\n\"You have been chosen for a glorious destiny!\"\n\nYou don't intend to wait and see what that 'glorious destiny' entails. However, as you turn to flee, the three raise their hands and begin an eerie magical chant.\n\nSmoke as thick and green as pond scum billows out of their sleeves and rolls across the room towards you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::NOOSE}))
        {
            return 111;
        }
        else
        {
            return 134;
        }
    }
};

class Story151 : public Story::Base
{
public:
    Story151()
    {
        ID = 151;

        Text = "The storm passes at last. You watch it swirl off into the north, a smudge of dust against the sharp line of the horizon.\n\nHakim gathers everyone together. After so many hours with the wind's roar filling your ears, you have to strain to make out his words. \"We have lost two camels...\" he is saying.\n\nYou glance around, finding one face missing. The young lad who gave the camels their fodder each evening. \"What about Hasib?\"\n\nA search is mounted, but there is no sign of Hasib. He is lost beneath the dunes that the storm left piled up in its wake. After stopping to pray, you head on until you see an oasis whose cool green shadows defy the desert's harsh golden dusk. Among the palm trees there are tents and even the turrets of an old fort. \"Do we dare approach?\" says Hakim. \"They might be hostile.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Counsel him to enter the oasis", 416));
        Choices.push_back(Choice::Base("You think it would be wiser to pass by", 438));

        Controls = Story::Controls::STANDARD;
    }
};

class Story152 : public Story::Base
{
public:
    std::string PreText = "";

    Story152()
    {
        ID = 152;

        Choices.clear();
        Choices.push_back(Choice::Base("Approach the oasis", 416));
        Choices.push_back(Choice::Base("Avoid the oasis", 438));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your next sensation is of being shaken awake. Your clothing is filled with sand and the others are leaning over you. \"You're alive!\" gasps Hakim. \"It's a miracle. You were under the quicksand for minutes on end, then you bobbed up to the surface.\"\n\nYou start to tell him about your strange adventure, then think better of it. It would sound as if you were raving mad. Passing your hand in front of your face, you realize that the experience has changed you. You have conquered the dread spirit of death that dwells in the desert's fastnesses. Now you can deal confidently with any threat the desert can throw at you.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            PreText += "\n\nYou have acquired the [WILDERNESS LORE] skill.";

            player.SKILLS_LIMIT++;

            player.Skills.push_back(Skill::WILDERNESS_LORE);
        }
        else
        {
            PreText += "\n\n[WILDERNESS LORE] You have gained 2 Life Points permanently.";

            player.MAX_LIFE_LIMIT += 2;

            Character::GAIN_LIFE(player, 2);
        }

        PreText += "\n\nGiving the quicksand a wide berth, you travel on until you see an oasis glittering like a green jewel in the hot golden haze of dusk. Among the trees you see people camped, and behind them is the outline of an old stone fort.";

        Text = PreText.c_str();
    }
};

class Story153 : public Story::Base
{
public:
    Story153()
    {
        ID = 153;

        Text = "You wake up feeling sick and lethargic. The sun is beating down on the planks of the deck, and the stink of festering corpses hangs heavy in the air.\n\nYou sit up, wincing, and look around. Your heart sinks as you realize that your own ship has gone. You are alone on a ship of dead men, drifting on the open ocean. Staggering over to inspect the hawser, you find it has been cut. Did your friends cast you adrift? It seems unbelievable -- but, if not, then who did?\n\nYou tip the corpses over the side. It is hard, unpleasant work that makes the thudding behind your eyes feel even worse. You are just dipping a cup into the freshwater barrel to slake your thirst when you remember that you did the same thing last night. In fact, it is the last thing you remember doing. You sniff the water, and now you can detect a faint flowery scent. It is poisoned. You are lucky to be alive.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            return 39;
        }
        else
        {
            return 62;
        }
    }
};

class Story154 : public Story::Base
{
public:
    Story154()
    {
        ID = 154;

        Text = "You retreat slowly, pulling the foliage around you like a cloak. The eye-slits of the mask turn in your direction, pause, then scan the rest of the glade. \"None remain,\" declares the noble voice.\n\nThe Sultan rides off, followed by his horsemen. You emerge from hiding, taking a last sad glance at your dead friends before moving off alone.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story155 : public Story::Base
{
public:
    std::string PreText = "";

    Story155()
    {
        ID = 155;

        Choices.clear();
        Choices.push_back(Choice::Base("Use a pair of MAGIC SLIPPERS", 336, {Item::MAGIC_SLIPPERS}));
        Choices.push_back(Choice::Base("Try a coil of INDIAN ROPE", 292, {Item::INDIAN_ROPE}));
        Choices.push_back(Choice::Base("You have a LONG TAILED CAT", 292, {Item::LONG_TAILED_CAT}));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "A week later, the grille is hauled up and another prisoner is lowered into the oubliette. \"Here is the real Shadow!\" calls down a guard. \"Now you worthless wretches have got some distinguished company for a change.\"\n\nThe grille drops back into place with a clang. \"What about me?\" you shout up. \"If you've got the real Shadow, you must know I'm innocent!\"\n\nThe guard's face reappears at the top. He has a broad smirk as he says, \"Innocent? You can't be innocent if you're in gaol, can you? So maybe you didn't steal the Sultan's ruby -- who cares? No doubt there's some other crime we can mark down to you.\"\n\n\"This is rank injustice!\" you call back, but he has gone.\n\nThe newcomer places a hand on your shoulder. \"I too am the victim of injustice, my friend, for I am not the Shadow. I thought you were. In fact, I got myself caught in order to meet you. My name is Azenomei.\" You turn and look at him: a handsome beardless young man with sparkling gaze. He has a small scar across the bridge of his nose.\n\n\"In that case, you're in for a big disappointment. And why are you smiling? Don't you know we'll probably stay here till we die?\"\n\nHis grin grows all the wider as he brings out a huge bunch of keys. \"Here I have the answer to nine hundred and ninety-nine locks. All we need is a way to reach the grille.\"";

        if (!Character::VERIFY_ITEMS_ANY(player, {Item::MAGIC_SLIPPERS, Item::INDIAN_ROPE, Item::LONG_TAILED_CAT}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nLacking any of those (MAGIC SLIPPERS, INDIAN ROPE, LONG TAILED CAT), you have no way of reaching the grille and you really will end your days in this miserable pit.";
        }

        Text = PreText.c_str();
    }
};

class Story156 : public Story::Base
{
public:
    Story156()
    {
        ID = 156;

        Image = "images/filler3.png";

        Text = "To your own amazement as much as that of the evil sorcerers, the cloud of green gas is absorbed by the black jewel you are carrying. You waste no time wondering about it, but launch yourself forward and snatch up the chart before racing from the room.\n\nThe sorcerers come tottering after you, but they are old and you soon outdistance them. Retrieving your belongings, you find the door and hurry down the hillside away from the fearful citadel.\n\nThe BLACK JEWEL has LOST its power.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::BLACK_JEWEL});

        Take = {Item::CHART};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 42; }
};

class Story157 : public Story::Base
{
public:
    Story157()
    {
        ID = 157;

        Text = "Losing your grip, you fall with a scream only for your shirt to catch on a spur of rock that juts out from the rock face. You are suspended above a sheer drop and you can hear the fabric starting to tear, but in front of you is a crevice that was previously hidden by the overhang.\n\nScrambling inside, you find a narrow fissure up through the pinnacle. It is a tight squeeze but, by bracing yourself against the sides, you are able to ascend all the way to the top.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 325; }
};

class Story158 : public Story::Base
{
public:
    Story158()
    {
        ID = 158;

        Text = "The rokh's beady gaze scours the land all around, but it does not notice you creeping over and taking hold of its tail feathers. With a sharp caw it launches itself into the sky and you are carried up and up until finally you reach the nest on the top of the pinnacle.\n\nThe LAMP of Antar is LOST. Its magic oil is now used up.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::LAMP_OF_ANTAR});
    }

    int Continue(Character::Base &player) { return 325; }
};

class Story159 : public Story::Base
{
public:
    Story159()
    {
        ID = 159;

        Text = "There is a sudden gust of occult wind, and you are sucked back in a dark spiral which conveys you to the Citadel of Bronze. Ayisha awaits you. She is still chained to the gold couch, but whereas before her pose was languid and resigned, now she is sitting forward eagerly.\n\n\"Did you get it?\" she asks. \"Did you get the key?\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::JEWELLED_KEY}))
        {
            return 424;
        }
        else
        {
            return 91;
        }
    }
};

class Story160 : public Story::Base
{
public:
    std::string PreText = "";

    Story160()
    {
        ID = 160;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Seen from the docks, the towers of Baghdad are like a carving of pale wood against the sky. Ships bob up and down at the quayside, sails wrapped tight around their high slender masts. You pass groups of sailors drinking wine and playing at dice, carousing now that the rigours of Ramadan are behind them.\n\nSeveral captains are hiring crew members.";

        auto pay = 3;

        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            pay = 3;

            PreText += "\n\nYou will only be trusted with menial tasks and your pay is just 3 dinars.";
        }
        else
        {
            pay = 8;

            PreText += "\n\nYou will be paid 8 dinars.";
        }

        Choices.push_back(Choice::Base("Sail east to the Indies", 229, Choice::Type::GAIN_MONEY, pay));
        Choices.push_back(Choice::Base("Sail westwards towards Egypt", 252, Choice::Type::GAIN_MONEY, pay));
        Choices.push_back(Choice::Base("Sail south in search of the fabled Scarlet Isle", 274, Choice::Type::GAIN_MONEY, pay));

        Text = PreText.c_str();
    }
};

class Story161 : public Story::Base
{
public:
    Story161()
    {
        ID = 161;

        Text = "Masrur's sword flashes like a lightning bolt in the lamplight. You do not even feel it cleave through your neck, and your eyes are already darkened by death when your head hits the floor at Jafar's feet. Your adventure has come to a grisly end.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story162 : public Story::Base
{
public:
    Story162()
    {
        ID = 162;

        Text = "The flag at the prow identifies this vessel as belonging to the Governor of Basra. Those are his elite guards, each of them more than a match for any common swordsman. Even if you are skilled in fighting, you do not relish a confrontation with six such doughty warriors.";

        Choices.clear();
        Choices.push_back(Choice::Base("Return to your ship", 375));
        Choices.push_back(Choice::Base("Approach the woman quietly", 140));

        Controls = Story::Controls::STANDARD;
    }
};

class Story163 : public Story::Base
{
public:
    Story163()
    {
        ID = 163;

        Text = "You snuff out the taper just before the monsters get within striking distance. Yussuf gives a long despairing wail of dread as darkness closes its robe around you.\n\nMoments trickle by. In the nerve-jangling silence, the only sound to be heard is the ragged rasp of Yussuf's desperate prayers: \"Merciful God, spare your unworthy servant. Never will I thieve nor cheat at dice again. No drop of wine will touch my lips -- \"\n\n\"Yussuf, listen!\" You reach out a hand in the dark and shake him until he regains his wits.\n\n\"There's nothing...\" he says in a wanly hopeful voice. \"What happened to the monsters?\"\n\nStepping back to find a rock to strike sparks with, you tread on something which squelches under your heel. Relighting the taper, you see that you have crushed a swarm of beetles. \"There are the monsters.\"\n\nYussuf gapes at them. \"Tiny insects! But those things we saw were huge.\"\n\n\"Illusions. The shape of our own fears.\" You peer into the gloom ahead. \"We must be on our guard, my friend. This is a place of dark sorcery.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 186; }
};

class Story164 : public Story::Base
{
public:
    Story164()
    {
        ID = 164;

        Text = "As you make your choice, the old man claps his hands and the mysterious light flares up, dazzling you. As your eyes clear, you find yourselves back on the ledge overlooking the river. There is no sign of the old man, nor any trace that his charcoal fire was ever here.\n\n\"How very strange,\" says Yussuf. \"I would think it all a dream, if not for the treasures we have with us. Who was the old man, I wonder?\"\n\n\"A ghost or jinni. Let's hope the treasures are not cursed.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::LAMP_OF_ANTAR, Item::INDIAN_ROPE});
    }

    int Continue(Character::Base &player) { return 256; }
};

class Story165 : public Story::Base
{
public:
    Story165()
    {
        ID = 165;

        Text = "The captain glowers as you kneel on the deck and unroll the mat. \"Save your prayers for later,\" he snarls. \"God is compassionate, but we cannot look to Him to guide us from this fog bank.\"\n\nThe mat falls with its gold fringe towards Mecca. You scan the charts, pointing to a jagged line that the map-maker has labelled with a warning. \"See this coral reef?\" you say to the captain. \"If I'm right as to our heading, it lies just a few leagues to starboard. I counsel you to steer well clear, or we'll run aground.\"\n\nHe stares at your prayer-mat, then tries it for himself. No matter how he unrolls it, it always falls the same way. \"It must be magical,\" he grumbles suspiciously.\n\n\"It is pious magic, at least. As reliable as any compass.\"\n\nFinally he agrees to steer the course you set. Slowly the current carries you clear of the dismal fog, and when the crew see the sun again they raise you on their shoulders with a cheer.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 234; }
};

class Story166 : public Story::Base
{
public:
    Story166()
    {
        ID = 166;

        Text = "You take a stroll through the dusty streets of red earth. Children follow you in silence. The adults have all gone with your captain to the headman's house. You see no wares to buy. When you pass the window of a house, you catch a brief glimpse on an old woman inside before the shutters are banged shut. A dog watches you without barking, then slinks off to lie in the shade beside an old well.";

        Choices.clear();
        Choices.push_back(Choice::Base("Look in the well", 212));
        Choices.push_back(Choice::Base("Go to the headman's house", 235));
        Choices.push_back(Choice::Base("Return to the ship", 189));

        Controls = Story::Controls::STANDARD;
    }
};

class Story167 : public Story::Base
{
public:
    Story167()
    {
        ID = 167;

        Text = "With Jumail nervously following a few steps behind, you thread your way along the narrow empty streets until you reach an ox cart not far from the headman's house. Barely have you hidden yourselves behind this when you see the islanders emerging from the building, dragging your captain whom they have bound with thick ropes. Despite the danger he is in, he is wrothly red and hurling eye-popping obscenities with his usual gusto.\n\n\"Swear and call upon your god all you like,\" you hear the headman say as the procession passes your hiding place. \"Tomorrow you will become a sacrifice to ours.\"\n\nThey take him and lock him inside a hut built of closely spliced hardwood logs. Two islanders are left to guard him while the others see to the grisly business of returning their dead ancestors to the cliffside tombs above the town.\n\nJumail is beginning to get cold feet. \"Poor old Captain Ibrahim,\" he whispers. \"It doesn't look like we've much chance of rescuing him, does it? I suppose we ought to get back before they catch us, too.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Return to the ship", 346));
        Choices.push_back(Choice::Base("Continue with the rescue attempt", 213));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            Choices[1].Destination = 190;
        }
        else
        {
            Choices[1].Destination = 213;
        }
    }
};

class Story168 : public Story::Base
{
public:
    Story168()
    {
        ID = 168;

        Text = "By noon of the following day your nostrils are thickly clogged with dusty sand stirred up by the wind. The sky resembles a plate of molten lead; the ground is hotter than a kiln.\n\nOne of your scouts returns and leads you and Hakim, the merchant, to a blue flag set on a long cane in the sand. \"What can it mean?\" Hakim wonders aloud. \"Is it a Bedouin grave?\"\n\nFalling to your knees, you begin to dig. \"God preserve us!\" cries the scout. \"Do you mean to loot the corpse?\"\n\nYou only laugh. \"There is no corpse here,\" you tell him. \"Quite the opposite.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 263; }
};

class Story169 : public Story::Base
{
public:
    Story169()
    {
        ID = 169;

        Image = "images/filler5.png";

        Text = "Drawing inspiration from the Lord of the Desert's taunts, your jinni uses his magic to transform you into a mouse. You scurry out of the alcove, but the enraged Lord pays no notice. Seeing the jinni's shadow beyond the curtain, he thinks he still has you trapped.\n\nYou run across the floor and up the steps, squeezing under the frame of the giant iron door just seconds before the spell wears off and you return to your normal form.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::RING});
    }

    int Continue(Character::Base &player) { return 459; }
};

class Story170 : public Story::Base
{
public:
    Story170()
    {
        ID = 170;

        Text = "You wait ten days until your owner and his camel-drivers return from Mecca. During that time, your thoughts were often of escape, but you know that running away would do you no good. You would soon be recaptured by the soldiers who patrol the pilgrim routes. The fate of a runaway slave does not bear thinking about.\n\nAs Hakim checks the straps of his camel's harness, he looks at you askance. Perhaps he has guessed what was in your mind, because he says: \"Wiser to stay with me. I treat you well enough. You're better off than most slaves, eh?\"\n\nYou return his gaze without expression. \"But still I am a slave,\" you say flatly.\n\nAt least you have had the opportunity to rest and regain your strength.\n\nYou RECOVER 1 Life Point.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 1);
    }

    int Continue(Character::Base &player) { return 123; }
};

class Story171 : public Story::Base
{
public:
    std::string PreText = "";

    Story171()
    {
        ID = 171;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "They are direly offended that you should spurn their hospitality. \"We offer you our only food, and you repay us by taking our pride instead!\" rages the chief. \"Begone! Perish in the wilderness, you ungrateful dogs!\"\n\nThey take up stones and start to pelt you. Seizing the halters of your camels, you retreat amid the dunes.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou can only nod when Hakim, the owner of the camel train, says: \"I am chastened. We are civilized men, yet we have had a lesson in honour from those who are almost too poor to afford the luxury of it.\"";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 217; }
};

class Story172 : public Story::Base
{
public:
    Story172()
    {
        ID = 172;

        Image = "images/filler4.png";

        Text = "The wind wraps a cloak of sand around you and pulls you off your feet. The camel's halter slips through your fingers. You give a startled cry, but it is torn from your lips and flung into the fury of the storm. You have a single glimpse of your companions' faces in the swirling gritty gloom. They stare in dismay to see you sucked into the air by the whirlwind. Then they drop away at dizzying speed and are lost to sight.\n\nYou hurtle through the heavens, flung between the dim gulfs of the clouds by the force of the storm. A leaden knell echoes inside your skull, sounding like the surge of waves heard from the ocean floor. You draw breath, but instead of sand you get a mouthful of salt water. Your last thought is that you are drowning beneath the sea -- surely the only traveller to do so while crossing the Arabian Desert!\n\nYou LOSE 1 Life Point.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 280; }
};

class Story173 : public Story::Base
{
public:
    Story173()
    {
        ID = 173;

        Image = "images/filler3.png";

        Text = "You jump aside as the Lord of the Desert charges forward. He careers past, robes fluttering, slashing madly with his sword, and rebounds from the wall full of fury. Holding his sword straight out in front of him, he thrusts towards your heart.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to dodge", 265));
        Choices.push_back(Choice::Base("Punch at him as he comes in close", 468));
        Choices.push_back(Choice::Base("Kick at his legs", 242));

        Controls = Story::Controls::STANDARD;
    }
};

class Story174 : public Story::Base
{
public:
    Story174()
    {
        ID = 174;

        Text = "The man you have caught gives his name as Jumal of Serendib. He admits to poisoning all of the crew of his own ship, but maintains that it was justified because they were unbelievers.\n\nThe captain, a perceptive man whose brother is a judge, soon sees the flaw in Jumal's argument. \"Obviously you were lying in wait till you could poison our water also!\" he cries. \"You unmitigated villain.\"\n\n\"You call me a villain,\" says Jumal, raising his finger, \"but I counter this with the charge that you are the villains. If you had learned of my quest for the diamond egg of the giant rokh, you would happily have murdered me for the secret.\"\n\n\"Sheer supposition!\" retorts the captain. \"Because you yourself are a treacherous pustule with the ethics of a starving hyena, you impute the same motives to others. Where is the rokh's nest, incidentally?\"\n\nUnder close interrogation, Jumal reveals that it is at the head of the Nile river. He also hands over a vial containing an all-purpose ANTIDOTE, which is given to you for safekeeping.\n\nYou gained the codeword KISMET.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::ANTIDOTE});

        Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});
    }

    int Continue(Character::Base &player) { return 197; }
};

class Story175 : public Story::Base
{
public:
    Story175()
    {
        ID = 175;

        Image = "images/city.png";

        Text = "You take stock of your surroundings with growing astonishment. The ship is caught in the branches of a large tree whose roots lie in the clouds. Cliffs like puffs of foam loom above a sheer drop of hundreds of feet to the sea below.\n\nSlowly, like a sleepwalker, Captain Ibrahim reaches out and plucks a violet flower from the bough of the tree. He sniffs at it, then drops it into your hand. \"It is real,\" he says, his gruff voice softened by awe.\n\n\"Look!\" cries one of the sailors. He is pointing at gleaming towers that are visible on the other side of a hillock of cloud.\n\n\"It is a city,\" says Captain Ibrahim, gradually recovering his wits. He turns to you. \"Go and investigate. The city's inhabitants may know of a way for us to reach the ground.\"\n\nYou cannot argue. It was you who got everyone into this mess. You dangle your legs over the side, surprised to find the cloud surface is solid and springy. It reminds you of moss. With a last forlorn look at the others, you trudge off towards the mysterious city.\n\nYou have gone only a few hundred yards when you hear the sound of a child crying. It seems to come from beyond a fleecy white bank.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go closer", 257));
        Choices.push_back(Choice::Base("Ignore the child and continue on to the city", 302));

        Controls = Story::Controls::STANDARD;
    }
};

class Story176 : public Story::Base
{
public:
    Story176()
    {
        ID = 176;

        Text = "Days pass without mishap, and at last a good following wind brings you to the port of Raysut.\n\nYou RECOVER 2 Life Points.\n\nBy now Captain Ibrahim is his old blustering self. Striding down the gangplank, he accosts a merchant on the seafront and asks the latest news.\n\n\"The Red Sea is unsafe for shipping by reason of pirates,\" announces the merchant. \"I myself lost a cargo of rugs that was bound for Cairo only last month.\"\n\nThe captain glowers like an angry old wolf. \"Pirates? Pah! Surely the Sultan's fleets can deal with them?\"\n\nAn old sailor who is passing by overhears this and stops to join in. \"These are no ordinary pirates. After each raid, they vanish like the dew in the gardens of Baghdad with the coming of dawn. I know, for I encountered them myself.\"\n\n\"And you survived?\" asks Yussuf the helmsman. \"How was that?\"\n\n\"Ah!\" declares the old sailor, raising his finger to the heavens. \"Now I shall tell you a tale of great wonder...\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Hang around and hear his story", 453));
        Choices.push_back(Choice::Base("Visit the market to do some shopping", 350));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 2);
    }
};

class Story177 : public Story::Base
{
public:
    Story177()
    {
        ID = 177;

        Image = "images/filler1.png";

        Text = "You wander for days in the hills until you find a trail that leads down into a region of steaming swampland. Skirting this, you travel on until you see a city of tall towers and eggshell domes straddling both sides of a great river. When you arrive at the gates, you enquire where you are.\n\nThe sentries give you an unwelcoming look. \"This is Daibul,\" they say. \"Be warned, we give short shrift here to penniless vagabonds.\"\n\n\"Perhaps I am no vagabond, but heir to a kingdom,\" you reply, sauntering between them into the teeming city streets. Seeing their curious looks, you laugh, adding, \"Or perhaps not. God alone is all-knowing!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 442; }
};

class Story178 : public Story::Base
{
public:
    Story178()
    {
        ID = 178;

        Text = "You dig at the interior of the lock using a thin metal sliver that you keep tucked in your boot. After a few seconds there is a heavy click and the lock springs open. Noiselessly raising the grille, you lope across the courtyard and make your getaway.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 223; }
};

class Story179 : public Story::Base
{
public:
    std::string PreText = "";

    Story179()
    {
        ID = 179;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "Without warning, he rounds on you and utters a spell.";

        if (!Character::VERIFY_ITEMS(player, {Item::Type::BLACK_JEWEL}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nYou are helpless to stop yourself falling on all fours -- or rather hoofs -- and you will spend the rest of your life as a jackass.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 202; }
};

class Story180 : public Story::Base
{
public:
    Story180()
    {
        ID = 180;

        Text = "It takes months, but at last, while sitting in a fisherman's shack on the fringe of the mangrove swamps outside Daibul, you hear confirmation of the legend.\n\n\"Indeed, I have seen the rokh,\" claims the fisherman. \"Its wingspan is so wide as to blot out the sun, and each claw could enfold a ship. Its beak is longer and sharper than -- \"\n\nYou give a cough. \"The important thing is, does it really lay diamond eggs?\"\n\nHe cackles wildly. \"I don't know, do I? I never visited the Isle of Palms myself, much less climbed to the rokh's eyrie.\"\n\n\"The Isle of Palms?\" you enquire. Suddenly, success seems within your reach.\n\n\"That's where it nests. If you want, I'll take you there tomorrow.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 21; }
};

class Story181 : public Story::Base
{
public:
    Story181()
    {
        ID = 181;

        Text = "At first the rocks are rough enough for you to climb quickly. As you get higher, though, you have to search more carefully for each handhold. Also the cliff is covered with patches of slippery moss, and twice you nearly lose your grip.\n\nYou look up. You don't seem to have got more than a third of the way, if that. You have no particular wish to look down and check.";

        Choices.clear();
        Choices.push_back(Choice::Base("Press on", 227));
        Choices.push_back(Choice::Base("Give up and return to the ground", 249));

        Controls = Story::Controls::STANDARD;
    }
};

class Story182 : public Story::Base
{
public:
    Story182()
    {
        ID = 182;

        Text = "Few people dare to venture outside after dark because of the curfew, so it is easy to spot the Caliph. He is wrapped in a dark cloak and accompanied by his hulking bodyguard, Masrur. You shadow them until they return to the palace, which they enter by means of a concealed tunnel. Following, you emerge from the darkness of the tunnel just as the Caliph is throwing off his disguise.\n\n\"An assassin!\" roars Masrur, stepping forward and raising his sword.\n\n\"Wait!\" you say to the Caliph, raising your hands to show they are empty. \"I have not come to harm you, O Prince of the Faith, but to warn you against treachery.\"\n\nThe Caliph considers for a moment, then nods and leads you to the end of the corridor. \"I'll hear what you have to say.\"\n\nYou follow him into the throne room, where you come face to face with your enemy Jafar. You see hatred blaze behind his eyes, but he quickly masks it with a laugh and says, \"Why, O Caliph, do you waste your time on the prattle of a guttersnipe such as this?\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 477; }
};

class Story183 : public Story::Base
{
public:
    Story183()
    {
        ID = 183;

        Text = "Arriving at the market in early morning, you see two teams of camels loaded for long journeys. Porters rush along the line, checking the wares are securely strapped. The camels growl like consumptive old men and glower disdainfully at their handlers, rising to their feet reluctantly as the first caravan moves off.\n\nA merchant approaches you and asks if you will hire on as a caravan guard. \"I will pay you ten dinars. Come, be quick about your answer -- those are my camels you see traipsing towards the eastern gate.\"\n\n\"Ten dinars to brave the blades of a thousand bandits!\" scoffs another man who has overheard this. He takes your arm and points to the other caravan, now making ready to set off. \"Why weigh your lifeblood against a pouch of gold? Come with us to Egypt. It's a safer route by far than this slave-driver takes.\"\n\nThe first merchant stares at him in express amazement. \"Safe, you claim? Your tongue is more wretched than a dog's tail! Is it safe to fling one's life at the mercy of the desert sun?\" He turns to you. \"Let this rogue pay you in water. You will need it more than my gold, if you take the route to Egypt.\"\n\nDecide.";

        Choices.clear();
        Choices.push_back(Choice::Base("Join the first caravan, heading east through the Peaks of the Slayers, for the sum of 10 dinars", 296, Choice::Type::GAIN_MONEY, 10));
        Choices.push_back(Choice::Base("Join the second caravan across the desert to Egypt for the sum of 6 dinars", 400, Choice::Type::GAIN_MONEY, 6));

        Controls = Story::Controls::STANDARD;
    }
};

class Story184 : public Story::Base
{
public:
    Story184()
    {
        ID = 184;

        Text = "You can hear murmuring and the rustling of silks as Jafar changes his robe in the next room. Since he is boasting loudly to the timid slave about his plans, it's unlikely he will hear you. Even so, you are careful to pad as quietly as a cat over to the table where the chart lies. Scanning it quickly, you see that the rokh's nest is marked close to the source of the Nile river.\n\nYou gained the codeword KISMET.\n\n\"These green slippers will not do!\" you hear Jafar hissing at his slave. \"Have you no sense at all, you curd-faced girl? Fetch the red pair from the other room.\"\n\nYou glance down. The red slippers are beside the table. You see the slave girl's swaying silhouette as she approaches the curtained archway. You must get away fast, or she will raise the alarm. Hastily you retrace your steps.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            return 383;
        }
        else
        {
            return 207;
        }
    }
};

class Story185 : public Story::Base
{
public:
    Story185()
    {
        ID = 185;

        Text = "You draw back to the stern, where the posts supporting the kiosk roof prevent the guards from coming at you all at once. Hearing the affray, the woman peeks out from behind the silk drapes and gives a shriek of dismay.\n\n\"Fear not, my lady!\" calls one of the guards. \"We'll soon despatch this rogue.\"\n\nThey might at that. You duck as the nearest guard swings his blade towards you. The steel hisses over your head and strikes the wooden rail with a dull thunk. As your opponent swears and twists at the sword to free it, you stamp on his foot and follow through with a desperate blow to his stomach. The others crowd in behind him, keen to try their mettle against you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::JEWELLED_SWORD}))
        {
            return 208;
        }
        else
        {
            return 231;
        }
    }
};

class Story186 : public Story::Base
{
public:
    Story186()
    {
        ID = 186;

        Text = "A single narrow passage slopes off from this cavern. You descend, steadying yourselves against the rock walls, until the flickering light of your taper reveals a room of worked stone just ahead. You see faded murals which show warriors in battle, fighting and dying to protect the idols of their false gods.\n\n\"These are scenes from a time before the light of truth was brought to mankind by the Prophet -- may all blessings be upon him,\" says Yussuf. He points to part of the mural. \"See these cloaked swordsmen with masks of iron. They are the fanatics of the god Mithra, who gave his followers great strength and courage in battle. Or so I have heard, but God alone is all knowing.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 232;
        }
        else
        {
            return 255;
        }
    }
};

class Story187 : public Story::Base
{
public:
    Story187()
    {
        ID = 187;

        Text = "No sooner have you made your choice than the old man claps his hands. At once the mysterious light flares up, dazzling you. When your eyes clear, you are back on the ledge overlooking the river. There is no sign of the old man, nor any trace that his charcoal fire was ever here.\n\n\"How very strange it all was,\" says Yussuf. \"A dream? Surely not, for how then can we account for these two treasures?\"\n\n\"Best we say nothing of this to the others. They would think us mad.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::INDIAN_ROPE, Item::JERICHO_HORN});
    }

    int Continue(Character::Base &player) { return 256; }
};

class Story188 : public Story::Base
{
public:
    Story188()
    {
        ID = 188;

        Text = "A thick vapour, darker than the mist, pours from your RING and congeals into a broad figure with eyes like hissing coals. The sailors fall flat on the deck in terror. Captain Ibrahim draws his sword and takes a step forward, but you place your hand on his wrist. \"Be calm. This grotesque ogre is my servant.\"\n\nThe jinni eyes you blackly. \"What service may I perform for you, O fount of one thousand virtues?\" he grates.\n\n\"Fill our sails with wind,\" you tell him. \"Carry us far out of this fog bank.\"\n\n\"I exist only to do your bidding,\" he replies, but you do not like the vicious smile on his gnarled features as he says this. Your worries are confirmed a moment later when, blowing hard into the lank sails, he propels the ship directly upwards out of the water. The sailors cling on to the rail for dear life. It is a miracle that no one falls to his death.\n\nComing to rest with a soft jolt, you think that the ordeal is over. You have landed, indeed -- but not back on the waves. Beneath you is a swirling mass of white. Your ship is suspended in the clouds!\n\nThe jinni swirls back into your RING. You exert your magic, brandishing the RING and sternly crying out, \"Jinni! I summon you to reappear!\"\n\n\"There is no jinni here,\" says a sullen voice from the RING. \"Just a grotesque ogre.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 175; }
};

class Story189 : public Story::Base
{
public:
    Story189()
    {
        ID = 189;

        Text = "The sun buries itself in a dry red haze over the western hills. Velvet darkness slides down to cover the landscape. From the headman's house you see a blaze of lights, but elsewhere the town is shrouded in darkness.\n\nThe stars emerge. As a chill breeze gusts along the river, Jumail the cook pulls his jerkin around his shoulders and says, \"I don't like it. What's happened to the captain? He ought to have got back by now.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Go ashore to look for him", 235));
        Choices.push_back(Choice::Base("Stay aboard", 258));

        Controls = Story::Controls::STANDARD;
    }
};

class Story190 : public Story::Base
{
public:
    Story190()
    {
        ID = 190;

        Text = "You wait until the dead of night, when both guards are deep in contented slumber. A glance to right and left confirms the streets are deserted. Sliding through the darkness, you creep up to the door of the hut. It only takes you seconds to spring the lock.\n\nThe captain looks up as the bar of moonlight strikes his face. Though startled, he has the sense to keep quiet as you lead him silently back towards the jetty.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 346; }
};

class Story191 : public Story::Base
{
public:
    Story191()
    {
        ID = 191;

        Text = "Hakim selects a man to scout ahead. This is Al-Shammar, a rangy Bedouin who carries an ivory bow with which you have seen him bring down wheeling gulls above the coastal road. He must be afraid to be sent on alone, but he counts it a point of pride to laugh and say, \"I shall see if there are indeed bandits in the pass -- and if there are, by my ancestors, I'll spit them each with an arrow.\"\n\nDespite these brave words, you never see Al-Shammar again. By the middle of the following morning, Hakim decides to risk pressing on. The cliffs rise up on each side and you all have the feeling of walking into the gates of a cursed city. The camels seem to sense the unease of their drivers. They lower their heads and growl at the ground like beaten dogs.\n\nYou scan the hills for bandits, but there is nothing. In the timid silence, the only sound to be heard is the desolate sigh of the wind in the rocks.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 289; }
};

class Story192 : public Story::Base
{
public:
    Story192()
    {
        ID = 192;

        Text = "Hakim sells you to a Frankish captain who is sailing with a hold full of lions and elephants to the court of an infidel king called Shah al-Ma'in. You adopt a surly scowl as you are led aboard his ship, but the truth is that your heart is brimming with hope. If you had run off before, your owner being a true believer, your only destiny would have been a painful death. But there is no penalty for slaves who run away from infidel owners. All you have to do, then, is come up with a plan of escape.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [SEAFARING]", 238, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("Use [ROGUERY]", 261, Skill::Type::ROGUERY));
        Choices.push_back(Choice::Base("Use [CUNNING]", 482, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("You have none of those skills", 103));

        Controls = Story::Controls::STANDARD;
    }
};

class Story193 : public Story::Base
{
public:
    Story193()
    {
        ID = 193;

        Text = "The Sultan decides to let you try your luck in catching the pirates. He has nothing to lose, after all. You are taken to a small port at the foot of Mount Sinai where you are entrusted with a vessel and a crew of thirty marines.\n\nYou put out to sea and sail around the coast for several days without seeing so much as a fishing boat. Your patience is finally rewarded one morning when the lookout calls out, \"Sails on the horizon!\"\n\nThe other vessel hoves into view. It turns out not to be the pirates, but a cumbrous merchant ship laden with wine barrels. Its captain obviously decided to risk passage across the Red Sea. You have a feeling his ship will make a choice target for the pirates.";

        Choices.clear();
        Choices.push_back(Choice::Base("Move in and hail the merchant ship", 239));
        Choices.push_back(Choice::Base("Keep it in sight without getting close", 476));

        Controls = Story::Controls::STANDARD;
    }
};

class Story194 : public Story::Base
{
public:
    Story194()
    {
        ID = 194;

        Text = "You find a jeweller who is willing to pay you thirty thousand dinars for the diamond.\n\n\"I thought it would be worth more.\"\n\nHe leans back, stroking his beard. \"Another may pay you twice as much, but such a one is not here. I offer a king's ransom that you can have today. Let wisdom guide you rather than greed, my friend.\"";

        Choices.clear();

        Controls = Story::Controls::SELL;
    }

    void Event(Character::Base &player)
    {
        Sell = {{Item::DIAMOND, 30000}};
    }

    int Continue(Character::Base &player) { return 251; }
};

class Story195 : public Story::Base
{
public:
    Story195()
    {
        ID = 195;

        Text = "Hakim is unsure what to do, and turns to you for advice.";

        Choices.clear();
        Choices.push_back(Choice::Base("You should press on in spite of the flag", 240));
        Choices.push_back(Choice::Base("Dig to see what it is marking", 263));
        Choices.push_back(Choice::Base("Agree with the scout that the group should head south-west", 286));

        Controls = Story::Controls::STANDARD;
    }
};

class Story196 : public Story::Base
{
public:
    Story196()
    {
        ID = 196;

        Image = "images/filler5.png";

        Text = "The jinni lays a finger along his nose and gives a sly wink. \"Remember the story of Mount Safa and the Prophet? When commanded to come to him, the mountain did not move. But the Prophet knew that if it had it would have brought disaster, so he set out to go to it.\"\n\n\"Your parable is too oblique for me,\" you say, shaking your head. He booms out a laugh that sends blue sparks flying through the rigging. \"Then watch and learn!\"\n\nDissolving into a cloud of pungent gas, the jinni floats down into the water. A thick dark patch of bubbling miasma goes snaking through the depths. A faint tinge of ammonia pervades the air.\n\nMinutes pass. Suddenly the stone door grates open and the pirates come swimming out, gasping and coughing. A strong stench billows after them. Even at this distance it is enough to make you dizzy. As the pirates are taken aboard and put in irons, the jinni leaps back into your RING in the form of a black fish.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 372; }
};

class Story197 : public Story::Base
{
public:
    Story197()
    {
        ID = 197;

        Text = "The remainder of the voyage is uneventful, and at last you reach the port of Daibul, which straddles a wide dun-coloured river beyond a region of mangrove swamps.\n\nThe captain goes ashore, returning quite soon with a broad smile on his face. \"I have sold all the cargo to a wealthy nobleman from Nishapur,\" he announces. \"Make ready. We sail on the tide.\"\n\nThe crew are surprised to be returning so quickly. They had expected that the captain's business would take at least a week. As the ship hoves out of port, you feel a sense of disappointment. \"Where is the adventure I longed for?\" you say with a sigh.\n\n\"Beware of wishing, so they say, lest you get what you wish for!\" replies the helmsman. \"See that dark scudding cloud across our bows? We're running into a storm.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 131; }
};

class Story198 : public Story::Base
{
public:
    Story198()
    {
        ID = 198;

        Text = "The jinni labours all night, piling stone on stone until he has built a tower as tall as the first. He slides the last block in place on the dome of the roof just as the sun thrusts up a splash of gold in the east. Flitting back to you, he wipes away the sweat covering his broad brow. \"I've done my part of the bargain, now do yours. Give me my freedom.\"";

        Bye = "Sunlight streaks the grass. One of the shark men steps forward and shakes his master awake. Opening his eyes, the dwarf gives a sour grunt of disappointment. \"So you did it.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Free him: throw the RING into the sea", 441, Choice::Type::LOSE_ITEMS, {Item::RING}));
        Choices.push_back(Choice::Base("Break your promise", 441, Choice::Type::GET_CODEWORD, {Codeword::Type::TRUCE}));

        Controls = Story::Controls::STANDARD;
    }
};

class Story199 : public Story::Base
{
public:
    Story199()
    {
        ID = 199;

        Text = "The horses pound up the path, rearing to a halt at the brink of the glass bridge. The four riders do not see you hiding in a thicket nearby because their attention is focussed on the jinni who, having taken your appearance, is standing in the middle of the bridge.\n\n\"Come and face me, dogs, if you dare!\" he screams. \"I yearn to spill your blood and crack the bones of your limbs between my teeth!\" \n\nYou wince. You might suggest he makes his performance a little less intense next time. But it seems to have done the trick. The first of the knights, goaded by his comrades, advances out onto the bridge. He slips and falls to his doom almost at once. The second knight fares better, getting halfway to the jinni before he too tumbles off. The third must be quite nimble -- he actually reaches the jinni and only slips because his sword-stroke costs him his balance.\n\nFrom your hiding-place, you hear the masked Sultan breathe a curse. His sword slithers from its sheath and he starts out along the bridge. Seven swift steps bring him to the jinni, who waits until the sword is in motion before dissolving into a cloud of vapour. The Sultan's lunge sweeps through empty air, and he spends an instant poised on the brink of eternity before following his knights down into the chasm.\n\nThe jinni returns to the RING beaming with satisfaction. \"I enjoyed that!\"\n\n\"All very well, but how am I going to get across?\" you ask.\n\n\"Just walk along the clifftop,\" he says, pointing. \"There's a perfectly safe footbridge after a mile or so.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story200 : public Story::Base
{
public:
    Story200()
    {
        ID = 200;

        Image = "images/creatures.png";

        Text = "The creatures facing you each have a single eye that rolls like a blister of pus in the centre of a face covered with bristles and scales. Their arms are raised like executioners' axes, each ending in a long curved blade of chitin. As they draw nearer you catch their breath, as fetid as an open drain. Slimy spittle runs from the writhing mandibles at the base of those repulsive insectoid heads.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            Choices.push_back(Choice::Base("Try to escape", 118));
            Choices.push_back(Choice::Base("Fight your way through them", 141));
            Choices.push_back(Choice::Base("Douse the light", 163));
        }
    }

    int Continue(Character::Base &player) { return 27; }
};

class Story201 : public Story::Base
{
public:
    Story201()
    {
        ID = 201;

        Text = "Squeezing through the bars of the grille, the hawk soars off into the night. You watch it go with a sense of misery. You cannot blame the bird for abandoning you -- it deserves its freedom -- but now you feel even more trapped.\n\nBarely a minute later, while you are still examining the lock, the hawk returns and settles on the ground. Hearing a metallic chink, you peer through the gloom. It has brought the keys from the guardhouse! Fingers trembling with anxious joy, you test each key in turn. One of them fits, and the padlock springs open. You are free.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 223; }
};

class Story202 : public Story::Base
{
public:
    std::string PreText = "";

    Story202()
    {
        ID = 202;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The BLACK JEWEL clouds and cracks as it absorbs the force of the spell. Azenomei shouts an obscene oath and draws his sword, flying at you in a fury. Strangely, it is only now that you notice his eyes. They are golden.\n\nThe battle is hard-fought and bloody. Soon you are gasping in the chill mountain air as you circle your foe looking for an opening. Blood streams from both of you. Azenomei's is black.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -4;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        if (player.Life > 0)
        {
            PreText += "\n\nyou finally succeed in clubbing Azenomei to the ground, where he gives a last gasp before dissolving into a thick tarry vapour.\n\nHis SWORD remains. The power of the BLACK JEWEL is now used up.";

            Character::LOSE_ITEMS(player, {Item::Type::BLACK_JEWEL});
        }

        Take = {Item::SWORD};

        Limit = 1;

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 42; }
};

class Story203 : public Story::Base
{
public:
    Story203()
    {
        ID = 203;

        Text = "The rokh's nest lies in the east, on the Isle of Palms. You manage to convince the fishermen to take you there in exchange for a share of the spoils.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 21; }
};

class Story204 : public Story::Base
{
public:
    Story204()
    {
        ID = 204;

        Text = "Decide what to do next.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use a LONG-TAILED CAT", 316, {Item::LONG_TAILED_CAT}));
        Choices.push_back(Choice::Base("Use an INDIAN ROPE", 360, {Item::INDIAN_ROPE}));
        Choices.push_back(Choice::Base("Climb up to the nest", 181));
        Choices.push_back(Choice::Base("Abandon the whole quest", 142));

        Controls = Story::Controls::STANDARD;
    }
};

class Story205 : public Story::Base
{
public:
    Story205()
    {
        ID = 205;

        Text = "You approach a richly-dressed slave outside the palace gates and explain that you have come to see Jafar. \"Tell him it is Shazir.\"\n\nHe peers at you in the dusk. \"Shazir? But I thought -- Well, never mind. Wait here while I find Jafar.\"\n\nYou catch his sleeve before he can move away. \"Jafar told me to come straight to him,\" you say, adding an undercurrent of menace to your tone. \"Things might go badly for you if there's any delay.\"\n\n\"Follow me,\" he says after a moment's thought.\n\nHe leads you to the throne room, where you see Jafar talking to the Caliph. The slave goes over, whispers something into Jafar's ear, and brings him over to the doorway where you're waiting.\n\n\"Have you brought the diamond...?\" says Jafar. His voice trails off as he gets a good look at you. \"You're not Shazir!\"\n\n\"No, and what I bring is something more precious than diamond. I bring the truth!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 477; }
};

class Story206 : public Story::Base
{
public:
    Story206()
    {
        ID = 206;

        Text = "You steal into the palace pretending to be a servant. The guards hardly glance at you, intent as they are on the festivities in the street outside. You pass under the great arch that is emblazoned with the Caliph's insignia, past a group of slaves bearing empty platters back to the kitchens, and duck into an open doorway. You have no clear idea what you can achieve here. Perhaps you can bluff your way into the Caliph's apartments and warn him about Jafar.\n\nFollowing a corridor, you make your way up a flight of stairs. You emerge onto a landing overlooking a torchlit hall. The marble walls shine with a colour like moonlight. There are rich tapestries of black, ruby-red and the blue of dusk, and the balustrade of the balcony is inlaid with gold and limpid mother of-pearl.\n\nAdvancing to the end of the balcony, you peer into a chamber beyond. Swords in jewelled scabbards hang along the walls, below murals that show the Caliph's ancestors in all the glorious panoply of war. As you cross the room, you notice an alcove where a hooded hawk sits on a perch.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take the HAWK", 318));
        Choices.push_back(Choice::Base("Arm yourself with one of the SWORDs", 450));
        Choices.push_back(Choice::Base("Otherwise", 93));

        Controls = Story::Controls::STANDARD;
    }
};

class Story207 : public Story::Base
{
public:
    Story207()
    {
        ID = 207;

        Text = "You are halfway along the landing when you hear a voice ring out behind you. \"What have we here? A skulking thief.\"\n\nYou whirl around, but you know it is Jafar even before you set eyes on his round hateful face. There is no mistaking those vicious tones, like the squawk of a vulture as it spies a carcass.\n\nA smile creases his fat lips. \"Well, well. You again. You must have more lives than a cat.\"\n\n\"You smirking villain. And you call me a thief...\" You take a step towards him.\n\nA glimmer of alarm shows in his tiny eyes. Clapping his hands, he calls in a quavering voice for the guards. Moments later, a band of swordsmen in the Caliph's livery come bursting from an archway at the end of the landing.\n\n\"Seize this cur!\" screeches Jafar.\n\nThe guards rush towards you.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::ARCHERY))
        {
            Choices.push_back(Choice::Base("Fight", 47));
            Choices.push_back(Choice::Base("Beat a hasty retreat", 253));
        }
    }

    int Continue(Character::Base &player) { return 230; }
};

class Story208 : public Story::Base
{
public:
    Story208()
    {
        ID = 208;

        Image = "images/filler4.png";

        Text = "The first guard slumps across the rail with a groan, his belly laid open by your sword-swipe. You are about to tip him over the rail and advance to meet the next guard when the lamplight flashes on the gems encrusting your weapon's pommel. The remaining guards stare at you wide-eyed and their leader holds up his hand.\n\n\"Wait,\" he says. \"In the night-time we mistook you for a river pirate, or some other knave with mischief in mind. Now I see you are a servant of our great lord the Caliph.\"\n\nYou lower your blade guardedly. This is a happy stroke of luck. \"Yes, the Caliph,\" you reply. \"May the blessing of God be upon him!\"\n\nBefore you can say more, the woman rises and ventures nervously out of the curtained kiosk. \"Tell me the Caliph has sent you to bring me back,\" she pleads. \"For if I am forced to enter the harem of the Governor of Basra, I shall take my own life.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell the guards you have come to take the woman", 254));
        Choices.push_back(Choice::Base("Bid them goodnight and return to your own ship", 375));

        Controls = Story::Controls::STANDARD;
    }
};

class Story209 : public Story::Base
{
public:
    Story209()
    {
        ID = 209;

        Text = "At last you manage to drive the loathsome creatures away. Those you have not killed go shuffling off into the recesses of the cavern. All around you are piled the cracked carapaces of their fellows, dripping dark ichor across the rocks. You pick your way through the carnage with a shiver of revulsion. Your own wounds are merging into a single throb of pain now, and your fervent prayer is that the other monsters do not return. You doubt if you could survive a second assault.\n\nWhen you go to help Yussuf to his feet, you are astonished to find him totally unscathed. \"They left me alone once I hid my face,\" he says, as surprised as you are at his lucky escape.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 186; }
};

class Story210 : public Story::Base
{
public:
    Story210()
    {
        ID = 210;

        Text = "Once you have picked them up, the old man claps his hands. The mysterious light flares up to fill the cavern, dazzling you. As your eyes clear, you find yourselves back on the ledge overlooking the river. There is no sign of the old man, nor any trace that his charcoal fire was ever here.\n\n\"How sweet the night air is,\" says Yussuf. \"I swear I never valued life half so much as I do now. We are lucky to be alive.\"\n\nYou nod in heartfelt agreement. \"God is compassionate and merciful. Let's go back to the ship, my friend.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::LAMP_OF_ANTAR, Item::JERICHO_HORN});
    }

    int Continue(Character::Base &player) { return 256; }
};

class Story211 : public Story::Base
{
public:
    Story211()
    {
        ID = 211;

        Text = "A dismal grey pall of fog hangs around the ship. Condensation drips from the rigging, making a soft whispering sound like fine rain on the decks. You are carried on blindly by the ocean current. There is no sign of the sun to help you steer a course, and in any case no wind to fill the sails.\n\nWithout warning, the ship lurches to one side. The stitched planks rip apart with the sound that every sailor dreads. You have time to glimpse hard jutting blocks of coral protruding through the broken hull. Then the mainmast snaps and the sail falls, enveloping you.\n\nYou hear the screams of the others as the ship goes down. Your fingers close on a spar of broken wood. Salt water fills your mouth and nose. You barely manage to struggle free of the wet sheet before it drags you under. Soaked through and buffeted by waves, you cling to the spar, drifting until at last you faint from grief and cold.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 280; }
};

class Story212 : public Story::Base
{
public:
    Story212()
    {
        ID = 212;

        Text = "At the bottom of the well, a glint of afternoon sunlight catches on something smooth and metallic. You are about to climb down when a stab of superstitious fear makes you hesitate. You know the old tales that say that wells and cisterns are the homes of demons.";

        Choices.clear();
        Choices.push_back(Choice::Base("Descend to see what the object is", 303));
        Choices.push_back(Choice::Base("Go back to the ship", 189));
        Choices.push_back(Choice::Base("Go up to the headman's house, where the captain was taken", 235));

        Controls = Story::Controls::STANDARD;
    }
};

class Story213 : public Story::Base
{
public:
    Story213()
    {
        ID = 213;

        Text = "An open assault is your best chance. You have to free the captain quickly, before the other islanders return from the tombs. Jumail is not certain he agrees, but he backs you up as you emerge from the cover of the ox cart.\n\nThe two guards leap up as they see you approaching. They have sharp hunting-knives almost as long as swords. You keep to a steady confident pace, neither hurrying nor hesitating, to show them you are a foe to be feared. As you draw near, you have the chance to size them up. The one on your left is small and wiry, and looks as though he is a nimble fighter best dealt with at close quarters. The other is huge and lumbering, with rock-hard knuckles that you'd do well to stay clear of.\n\nYou step up onto the porch. The two men are on either side of you. The look in their eyes is a turbid mixture of surprise, amusement, uncertainty and fear.";

        Choices.clear();
        Choices.push_back(Choice::Base("Deal with the smaller one", 236));
        Choices.push_back(Choice::Base("Deal with the larger one", 259));
        Choices.push_back(Choice::Base("Deal with both at once", 282));

        Controls = Story::Controls::STANDARD;
    }
};

class Story214 : public Story::Base
{
public:
    Story214()
    {
        ID = 214;

        Text = "Hakim asks if you will go ahead of the main group and see if there are bandits lying in wait. \"It is a dangerous job,\" he admits, \"and I will pay you two dinars.\"\n\n\"Two dinars for my life? That is hardly fair.\"\n\nHe nods. \"Three, then.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Accept", 478, Choice::Type::GAIN_MONEY, 3));
        Choices.push_back(Choice::Base("Point out that is not in your contract to take such risks", 191));

        Controls = Story::Controls::STANDARD;
    }
};

class Story215 : public Story::Base
{
public:
    Story215()
    {
        ID = 215;

        Text = "The talk on the streets of Cairo is mostly of the Red Sea pirates. Small children are enthralled by the stories, but none of the adults of the city has a good word for the pirates. \"Prices have doubled in the last two months,\" complains a shopkeeper. \"No one dares to travel by sea, and perishable goods cannot survive the slow journey by camel. I have not had a properly spiced meal since the end of Ramadan.\"\n\nYou soon learn that the Sultan of Cairo has promised a reward for the one who puts a stop to these pirates. One thousand dinars. That would make you as rich and respected a citizen as any in Baghdad.";

        Choices.clear();
        Choices.push_back(Choice::Base("Offer your services in catching the pirates", 306));
        Choices.push_back(Choice::Base("Visit the bazaar", 328));
        Choices.push_back(Choice::Base("Leave the city", 349));

        Controls = Story::Controls::STANDARD;
    }
};

class Story216 : public Story::Base
{
public:
    std::string PreText = "";

    Story216()
    {
        ID = 216;

        Choices.clear();
        Choices.push_back(Choice::Base("Stand your ground", 332));
        Choices.push_back(Choice::Base("Retreat", 46));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The demon descends and flails at you with its thin claws. Most horrible of all is the soft hissing cry which sounds like the dying gasps of a thousand souls.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -1;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nThe demon breaks off the fight and rises on humming wings to hover just above your head. You managed to deal it a couple of strong blows, breaking its hard exoskeleton, but now you see that it is regenerating. In front of your eyes, its wounds are disappearing.";
        }

        Text = PreText.c_str();
    }
};

class Story217 : public Story::Base
{
public:
    Story217()
    {
        ID = 217;

        Text = "By noon of the following day your nostrils and eyes are raw with the fine gritty sand stirred up by the wind. The sky is a plate of molten lead, the ground hotter than a kiln.\n\nOne of your scouts returns and leads you and Hakim, the merchant, to a blue flag set on a long cane in the sand. \"What can it mean?\" Hakim wonders aloud. \"Is it a Bedouin grave?\"\n\n\"More likely a warning that the region ahead is off limits to travellers,\" suggests the scout. \"We should turn south-west, master.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::MORDANT}))
        {
            return 286;
        }
        else
        {
            return 195;
        }
    }
};

class Story218 : public Story::Base
{
public:
    Story218()
    {
        ID = 218;

        Text = "The days crawl by. The sun, a boulder of light rolling relentlessly across the sky, plummets each evening beyond the edge of the world, draining all heat behind it so that you are left shivering in the chill of night. Even with strict rationing, you soon have barely enough water to moisten your lips, and barely food enough to make one mouthful at supper.\n\nYou have almost lost hope when, in the long shadows of dusk, you see an olive-green splash of colour against the dusty ochre landscape. You blink, rubbing your eyes to make sure, then call back to the others: \"An oasis!\"\n\nHakim stumbles forward. Barely able to stand, he leans on your shoulder and peers into the middle distance. \"Yes, but look. See those tents? That smoke from campfires? Do we dare risk provoking the inhabitants? If they're hostile, we're too weak to put up a fight.\"\n\nWhat will you advise?";

        Choices.clear();
        Choices.push_back(Choice::Base("Stop at the oasis", 416));
        Choices.push_back(Choice::Base("Go past and hope to find water elsewhere", 438));

        Controls = Story::Controls::STANDARD;
    }
};

class Story219 : public Story::Base
{
public:
    Story219()
    {
        ID = 219;

        Text = "You jump aside as the Lord of the Desert charges forward. He careers past, robes fluttering, slashing madly with his sword, and rebounds from the wall full of fury. Holding his sword straight out in front of him, he thrusts towards your heart.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to dodge", 265));
        Choices.push_back(Choice::Base("Punch at him as he comes in close", 468));
        Choices.push_back(Choice::Base("Kick at his legs", 242));

        Controls = Story::Controls::STANDARD;
    }
};

class Story220 : public Story::Base
{
public:
    Story220()
    {
        ID = 220;

        Text = "When the jinni sees what is happening, he unleashes a freezing gust of air from his lungs that turns the waves around the ship to ice. Some of the monkeys escape into the trees, but many are trapped by the frozen water. Swirling out on a column of blue-grey gas, the jinni retrieves some of what they filched, returning it to you. You have lost one of your possessions, however.";

        Choices.clear();
        Choices.push_back(Choice::Base("Abandon ship and see if you can survive in the swamp", 85));
        Choices.push_back(Choice::Base("Stay aboard and let the ocean current carry you onwards", 266));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        ToLose = {};

        Limit = 0;

        if (player.Items.size() > 0)
        {
            if (player.Items.size() == 1)
            {
                Character::LOSE_ITEMS(player, {player.Items[0].Type});
            }
            else
            {
                ToLose = player.Items;

                Limit = player.Items.size() - 1;
            }
        }
    }
};

class Story221 : public Story::Base
{
public:
    Story221()
    {
        ID = 221;

        Image = "images/filler3.png";

        Text = "Collecting the turbans of everyone in the crew, you knot them together to make a long cloth. You stretch this right around the circumference of the tower. It gives you the purchase you need to slowly ascend to the top.\n\nSurmounting the balcony, you drop to a wary crouch and survey the chamber under the dome. It is bare of any decoration or feature except for a podium in the middle, where a large grey egg rests on a velvet cushion.\n\nYou step forward. The whole tower must have been built for the single purpose of keeping this egg safe.";

        Choices.clear();
        Choices.push_back(Choice::Base("Touch the egg", 290));
        Choices.push_back(Choice::Base("Climb back down to the ground", 267));

        Controls = Story::Controls::STANDARD;
    }
};

class Story222 : public Story::Base
{
public:
    Story222()
    {
        ID = 222;

        Text = "The Sultan leaps down from his horse. His sword leaves its scabbard with a hard ringing sound. He waits like a statue, sword-tip touching the ground. The mask remains inscrutable, but his stance conveys absolute certainty. He believes you are no threat.\n\nYou take a wary half-step forward. His left hand hovers ready to lift his mask.";

        Choices.clear();
        Choices.push_back(Choice::Base("[ARCHERY] Use a BOW", 268, Skill::Type::ARCHERY));
        Choices.push_back(Choice::Base("Use a MIRROR", 291, {Item::MIRROR}));
        Choices.push_back(Choice::Base("Use a CLOAK", 313, {Item::CLOAK}));
        Choices.push_back(Choice::Base("You have none of those", 335));

        Controls = Story::Controls::STANDARD;
    }
};

class Story223 : public Story::Base
{
public:
    std::string PreText = "";

    Story223()
    {
        ID = 223;

        Choices.clear();
        Choices.push_back(Choice::Base("Go on with your meal", 463));
        Choices.push_back(Choice::Base("Follow them to see what they are going to do", 471));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You lose no time putting a good distance between you and the city where you were imprisoned. Your journey takes you up into high crags. The sky looks dark and storm-laden. The white sheen of snow lies on the tallest peaks above you.\n\nDays pass without any sign of habitation. You eke out your food under the rocks -- mostly grubs, insects and berries.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            Character::GAIN_LIFE(player, -1);

            PreText += "\n\nYou LOSE 1 Life Point.";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nAt last, hungry and cold, you stumble on a palace of ash-grey stone that seems to loom like a bank of cloud against the ominous sky. You climb the path towards it. Bronze gates swing open at your approach, and servants emerge to help you inside. Too weary to question them, you allow yourself to be led to a table where you are presented with dishes of honey-cake, roast fowl, mutton stew, plums and figs, spiced bread and sharp clean meltwater.\n\nYou eat so ravenously that at first you do not notice three dignified old men in scarlet robes who have quietly entered the room. As you look up, one of them raises his hand and smiles. \"Please, eat your meal,\" he says. \"Later we'll have a chance to talk.\"\n\nYou rise and bow. \"I must thank you for your hospitality.\"\n\n\"Later. We have something to attend to first.\"\n\nThey turn and glide out of the room, long robes rustling on the marble floor.";
        }

        Text = PreText.c_str();
    }
};

class Story224 : public Story::Base
{
public:
    Story224()
    {
        ID = 224;

        Text = "You find Azenomei reclining on a divan in one of the citadel's many rooms. \"I thought you said we had to hurry,\" you say. \"Come on -- what if the jinni should return and find us here?\"\n\nHe rises languidly to his feet. \"He has returned. I am the jinni whose palace this is.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 247; }
};

class Story225 : public Story::Base
{
public:
    Story225()
    {
        ID = 225;

        Image = "images/smoke-filled-room.png";

        Text = "Pulling your arms close to your sides to avoid touching the muck and grime of the tunnel walls, you tread carefully forward through the darkness until you see a flicker of torchlight ahead. You emerge in the crawl space below a large low-raftered house. Through a crack in the floorboards over your head, you see a strange scene. The islanders are bowing in homage to a group of rug-cloaked figures sitting on carved teak benches. Your captain stands between the two rows of seated figures as though he were on trial.\n\nYou hear him speak: \"What is this? Why have I been brought here?\"\n\nThe voice that replies sounds like the rustling of dead grass. It seems to come from one of the cloaked figures. Through the smoke-filled air of the room you catch sight of a lidless gaze. A hand like old clay clutches at the folds of the rug as it says, \"You came to steal the egg of the rokh, the giant bird that has its nests in the mountains above the Nile. Do not deny it.\"\n\n\"Preposterous!\" retorts Captain Ibrahim. \"I do not even believe the rokh truly exists.\"\n\nHis interrogator is not deterred. \"Tonight you will be imprisoned. Tomorrow our living descendents will put you to death.\"\n\nYou gained the codeword KISMET.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});
    }

    int Continue(Character::Base &player) { return 77; }
};

class Story226 : public Story::Base
{
public:
    Story226()
    {
        ID = 226;

        Text = "You remember hearing a tale about the rokh, which is said to swoop through the skies near to the Isle of Palms. It is so big that sometimes it seizes ships out of the water. The Isle of Palms lies in the far east, so that is where your destiny must take you. You manage to convince the fishermen to take you there in exchange for a share of the spoils.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 21; }
};

class Story227 : public Story::Base
{
public:
    Story227()
    {
        ID = 227;

        Text = "By the time you are halfway, and the ground is no more distant than the wisps of cloud above, you are beginning to wonder what you've let yourself in for. You are not even sure if you could get back down now. Equally, the cliff is so smooth and sheer that your fingers and legs are aching with the strain. If you go on, you might easily drop from fatigue.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL_ITEM(player, Skill::Type::AGILITY, Item::Type::JASMINE_FLOWER))
        {
            return 272;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 249;
        }
        else
        {
            return 294;
        }
    }
};

class Story228 : public Story::Base
{
public:
    Story228()
    {
        ID = 228;

        Text = "Jafar utters a mad laugh as he throws the knife. Rolling forward in a somersault, you pluck it out of the air before it can strike the Caliph, who is rooted to the spot in shock. As Jafar runs off, the Caliph recovers enough to call for his guards.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 339; }
};

class Story229 : public Story::Base
{
public:
    Story229()
    {
        ID = 229;

        Text = "The sails bulge as they catch the wind, putting you in mind of overfull waterskins. Slowly your vessel edges out from the dock and glides gracefully downriver towards Basra. The sun rises, turning the bowl of the sky to flaring azure. Long banners of white cloud hang across the heavens, while below the river swirls with rich green darkness.\n\nAt dusk on the sixth day out of Baghdad, as the ship is moored for the night, a sailor whose name is Yussuf suggests taking a swim. \"Toiling in the rigging all day is hot work,\" he says, grinning wearily as he wipes his brow. \"As the Prophet has warned us against the perils of wine, perhaps a plunge in the cool river water would refresh us just as well.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Go for a swim", 474));
        Choices.push_back(Choice::Base("Otherwise", 375));

        Controls = Story::Controls::STANDARD;
    }
};

class Story230 : public Story::Base
{
public:
    Story230()
    {
        ID = 230;

        Text = "Seeing you nock an arrow, the foremost guard skids to a halt on the marble floor. The others tumble into him from behind and they stand there silently for a moment, glowering at you.\n\n\"Fools! What are you waiting for?\" screeches Jafar. \"The arrow can only kill one of you.\"\n\nYou smoothly swing the arrow around to point at him. \"Then tell them to charge now,\" you say with a sly smile.\n\nHe holds up a fat jade-ringed hand. \"Wait! Hold your ground,\" he blusters at the guards. A trickle of sweat escapes the confines of his satin turban and rolls down into the plump clefts between his narrow eyes.\n\n\"That's better.\" You back away carefully and start to descend the stairs. Your arrow remains trained on Jafar's heart. \"I'm leaving now, Jafar, but I just want you to know that I'll be back. And I'll bring proof of your treachery before the Caliph.\"\n\nAs you reach the door, you release the arrow. It whips through the air, pinning Jafar's turban to the door behind him. Startled for a moment, he gives a sigh of relief and then points a trembling finger at you. \"Get the assassin!\"\n\nHe deserves to die, certainly, but that must wait until another day. You desire justice as much as revenge. Turning, you run back out of the palace and lose yourself in the side streets.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 383; }
};

class Story231 : public Story::Base
{
public:
    std::string PreText = "";

    Story231()
    {
        ID = 231;

        Image = "images/filler1.png";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You have rarely faced a more desperate test of your courage. Blows rain down on you, and it is all you can do to duck and weave fast enough to avoid being cut to bloody tatters.\n\n";

        auto DAMAGE = -7;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -3;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -5;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 277; }
};

class Story232 : public Story::Base
{
public:
    Story232()
    {
        ID = 232;

        Text = "You have also heard myths of the old days, when men worshipped a profusion of strange deities. Mithra was said to bestow invulnerability on his most devout followers, so that no weapon had the power to harm them. When they needed to settle duels among themselves, as honour would sometimes dictate, they had to resort to boxing and wrestling because these skills involve no weapons.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 255; }
};

class Story233 : public Story::Base
{
public:
    Story233()
    {
        ID = 233;

        Text = "You mentioned four treasures. There are no more in the chest. Is the last that BLACK JEWEL you wear?\"\n\nHe takes the JEWEL from around his neck and hands it to you. \"This little trinket? A charm against baneful magic. Take it if you wish.\"\n\nYussuf selects the INDIAN ROPE, which he gives to you for safe keeping.\n\nSmiling, the old man brings his hands together. There is a noise like a thunderclap and a blaze of white light, and then you are standing in the open air again. You are on the ledge above the river, with no sign now of the cavern or the old man.\n\n\"Strange magic,\" whispers Yussuf. \"If we tell the others about this, they'll think us mad.\"\n\n\"So we won't tell them.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::INDIAN_ROPE});

        Take = {Item::BLACK_JEWEL};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 256; }
};

class Story234 : public Story::Base
{
public:
    Story234()
    {
        ID = 234;

        Image = "images/filler4.png";

        Text = "The days stream by and you lose yourself completely in the tranquil pleasure of the sea's rhythms.\n\nYou RECOVER 2 Life Points.\n\nAt night the stars look down upon your progress, blistering beacons placed in their courses by divine providence as a guide for seafarers. By day the sun shimmers from a sky of eggshell blue. You listen to the slow gentle creak of the rigging, the slosh of the waves, and the murmur of the ship's boards. Gulls follow your course, hunting the fish that your passage stirs up to the surface.\n\nDriven by north-east monsoon winds, you make good speed and in three weeks the peaks of the Scarlet Isle can be seen thrusting up from the horizon. Here you see the reddish tinge to the water that gives the island its name. \"Some say it is the blood of the warlike tribes who live there,\" says one man in a voice hushed with fear of the unknown.\n\n\"Bah!\" says the captain, hearing this. \"It is nothing more than the minerals carried out to sea by the rivers.\"\n\nFinding an estuary, you cruise upstream until you see the roofs of a town. Buildings of mud-brick squat dustily amid the crags, fields laid out in front of them like rolling carpets of emerald and golden thread. As you tie up at the dock, a crowd of natives come down from the houses to meet you. They are garbed in long robes of beige cloth, belted at the waist, and each wears a long gold-hilted knife at his side.\n\nCaptain Ibrahim leaps ashore. \"Stay with the ship,\" he tells the rest of you. \"I'm going to speak with their headman.\" So saying, he strides off and is escorted by the natives back to a large building in the centre of the town.";

        Choices.clear();
        Choices.push_back(Choice::Base("Disembark", 166));
        Choices.push_back(Choice::Base("Stay on board as ordered", 189));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 2);
    }
};

class Story235 : public Story::Base
{
public:
    Story235()
    {
        ID = 235;

        Text = "The other sailors are too frightened to come with you. Alone, you make your way through the empty streets to the headman's house. Now you can see that beyond it, lining the cliffs, are rows of tombs. The boulders that normally seal them have been rolled back, and emerging from them are a group of islanders bearing smoking torches. Each carries something across his shoulders -- something long, wrapped in thick rugs like shrouds. You have the sudden conviction that they are dead bodies.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go back to the ship", 258));
        Choices.push_back(Choice::Base("Sneak into the building", 281));

        Controls = Story::Controls::STANDARD;
    }
};

class Story236 : public Story::Base
{
public:
    Story236()
    {
        ID = 236;

        Text = "How will you attack?";

        Choices.clear();
        Choices.push_back(Choice::Base("[SWORDPLAY] Use a SWORD", 304, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::JEWELLED_SWORD}));
        Choices.push_back(Choice::Base("You do not possess a SWORD or do not wish to use it", 326));

        Controls = Story::Controls::STANDARD;
    }
};

class Story237 : public Story::Base
{
public:
    std::string PreText = "";

    Story237()
    {
        ID = 237;

        Choices.clear();
        Choices.push_back(Choice::Base("Run forward across the parade ground", 216));
        Choices.push_back(Choice::Base("Stand firm", 332));
        Choices.push_back(Choice::Base("Retreat", 46));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "It drops on you with a voiceless shriek of glee. The talons dig deep into your neck, and you cannot stifle a scream of unendurable pain.\n\n";

        auto DAMAGE = -3;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -2;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        if (player.Life > 0)
        {
            PreText += "\n\nYou feel the demon release you and retreat into the air. You must have managed to hurt it. Through red waves of pain, you see its carapace reknitting, the wounds you struggled so hard to inflict vanishing in seconds.\n\nHow can you win against such a creature?";
        }

        Text = PreText.c_str();
    }
};

class Story238 : public Story::Base
{
public:
    Story238()
    {
        ID = 238;

        Text = "The ship puts out of harbour and begins the journey downriver to the Mediterranean. You soon show that you are too useful to waste at the oars, and various minor deck duties are assigned to you.\n\nOnce clear of Alexandria and onto the open sea, the captain has your shackles removed. \"Ten leagues of empty ocean,\" he says with a laugh, sweeping his hand astern of the ship. \"That ought to make you think twice about running away.\"\n\nThat night you slip over the side. The captain thinks no-one could swim all the way back to land, but you were brought up on a river boat that plied the stretch from Basra to Baghdad. A fish is no more at home in the water than you.\n\nYou reach the shore with aching limbs, shivering from the cold, but you are alive. No doubt when you're discovered missing they will assume you fell overboard and drowned. Few Frankish sailors can swim.\n\nYou find employment on a barge bound for Cairo, arriving there a few days later. The barge owner rewards you with 2 dinars for helping him unload his cargo.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::MORDANT);

        Character::GAIN_MONEY(player, 2);
    }

    int Continue(Character::Base &player) { return 215; }
};

class Story239 : public Story::Base
{
public:
    Story239()
    {
        ID = 239;

        Text = "The captain of the merchant ship loudly dismisses your suggestion that he might be attacked by pirates. \"We are only one vessel!\" he retorts.\n\n\"You are almost the only vessel on the Red Sea,\" replies the officer in charge of your marines. \"They'll take you as surely as wild dogs would help themselves to a fat goose.\"\n\nThe captain takes umbrage at this comparison, but you see a look of unease on his sailors' faces. \"Er, Captain,\" suggests his first mate, \"why don't we let those marines hide themselves in some of the barrels? That way, if the pirates do attack, they'll be in for a surprise.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Agree with that plan", 100));
        Choices.push_back(Choice::Base("Let the merchant ship get a little way ahead as bait for the pirates", 476));

        Controls = Story::Controls::STANDARD;
    }
};

class Story240 : public Story::Base
{
public:
    std::string PreText = "";

    Story240()
    {
        ID = 240;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The sun pours down a ceaseless stream of blistering heat. By mid afternoon you are reeling with heat exhaustion. The landscape looks like the barren plains of Hell. When you say as much to one of the camel drivers, he replies, \"Except that to enter Hell a man must die. In the case of the desert, death is the only escape.\"\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_ITEMS(player, {Item::Type::HAWK}))
        {
            DAMAGE = -1;

            PreText += "[Item: HAWK] ";
        }

        Character::GAIN_LIFE(player, -DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nYou press on across the hard rocky terrain. Dust rises from your footsteps and hangs like smoke in the air. At nightfall you watch the moon rise and wonder if you will live to see another day.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::HAWK}))
        {
            return 458;
        }
        else
        {
            return 373;
        }
    }
};

class Story241 : public Story::Base
{
public:
    Story241()
    {
        ID = 241;

        Text = "Your arrow whistles through the air and sends a spurt of blood from the chief's head. He raises his hand, face blank with shock, and finds that your shot has sliced off his ear. Waving his spear, he orders his men to break off the attack. You watch them go with relief, waiting until they are out of sight before you lower your bow.\n\nHakim clasps your neck and showers you with kisses. \"I owe you my life!\" he sobs. \"We all do. From this day, Hakim of Baghdad is as a brother to you. Here, this pouch of gold is a poor reward, but treat it as the merest token of my esteem.\"\n\nHe has given you 50 dinars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 50);
    }

    int Continue(Character::Base &player) { return 218; }
};

class Story242 : public Story::Base
{
public:
    Story242()
    {
        ID = 242;

        Text = "His shins are like iron. You stumble back after your kick, wincing in pain. It feels as though you have broken a toe. The only effect it had on the Lord of the Desert was to throw him off balance so that his sword-tip barely grazed your face.\n\nYou LOSE 1 Life Point.";

        Choices.clear();
        Choices.push_back(Choice::Base("Dodge", 219));
        Choices.push_back(Choice::Base("Attack", 288));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }
};

class Story243 : public Story::Base
{
public:
    std::string PreText = "";

    Story243()
    {
        ID = 243;

        Choices.clear();
        Choices.push_back(Choice::Base("Abandon ship and see if you can survive in the swamp", 85));
        Choices.push_back(Choice::Base("Stay aboard and let the ocean current carry you onwards", 266));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        ToLose = {};
        Limit = 0;

        if (!Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            PreText = "You check your belongings. To your dismay, the hairless monkeys made off with all your money and the first two items listed among your possessions.";

            player.LostMoney = player.Money;
            player.Money = 0;
        }
        else
        {
            PreText = "You check your belongings. To your dismay, the hairless monkeys made off with two items listed among your possessions but failed to find your money.";
        }

        if (player.Items.size() < 3 || !Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            for (auto i = 0; i < 2; i++)
            {
                if (player.Items.size() > 0)
                {
                    auto item = player.Items[0];

                    player.LostItems.push_back(item);

                    player.Items.erase(player.Items.begin());
                }
            }
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::LUCK) && player.Items.size() > 2)
        {
            ToLose = player.Items;

            Limit = player.Items.size() - 2;
        }

        PreText += "\n\nNow you face a fateful decision.";

        Text = PreText.c_str();
    }
};

class Story244 : public Story::Base
{
public:
    Story244()
    {
        ID = 244;

        Text = "The hawk flies up, spiralling around the tower to perch on the balcony. It disappears inside the dome, reappearing moments later with something clutched in its talons. It swoops down, and in the fading daylight you see that it has found a large grey egg, which it deposits on the turf at your feet.\n\nYussuf the helmsman spits in annoyance. \"I thought there'd at least be a jewelled necklace or something up there.\"\n\n\"Perhaps it is the diamond egg of the rokh?\" suggests Selim the look-out.\n\nYou shake your head. \"Not if the legends are true. The rokh's egg would be bigger than an elephant. Anyway, whatever that is, it isn't diamond.\"\n\nWill you touch the egg?";

        Choices.clear();
        Choices.push_back(Choice::Base("Touch the egg", 290));
        Choices.push_back(Choice::Base("You think it might be dangerous", 267));

        Controls = Story::Controls::STANDARD;
    }
};

class Story245 : public Story::Base
{
public:
    std::string PreText = "";

    Story245()
    {
        ID = 245;

        Bye = "You manage to drive the knights back and they abandon the struggle. Mounting up, they ride off after their master.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "The three attack as one, launching themselves from horseback with spears raised. Straight away you see that just one of these men would be a hard foe. Together they are almost unbeatable.";

        if (!Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}) && !Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nWithout combat skills you have no chance and are cut down at once.";
        }
        else
        {
            PreText += "\n\n";

            auto DAMAGE = -6;

            if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
            {
                DAMAGE = -3;

                PreText += "[SWORDPLAY] ";
            }
            else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
            {
                PreText += "[WRESTLING] ";
            }

            Character::GAIN_LIFE(player, DAMAGE);

            PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story246 : public Story::Base
{
public:
    std::string PreText = "";

    Story246()
    {
        ID = 246;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The jinni swirls out through the bars of the grille, hanging above you in the moonlight in a dark swirling cloud from which his face peers tenebrously. \"What do you desire?\"\n\n\"My freedom!\" you hiss back at him.\n\n\"As do we all,\" he replies with a resounding sigh.\n\nHe mutters a spell and you feel a tingling in your muscles. It feels as if you are being squeezed and stretched. A moment later you have become a snake. Quickly you slither through the grille.";

        if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::TRUCE}))
        {
            PreText += "\n\nYou wait for the jinni to turn you back to normal and then you scurry away from the prison.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::TRUCE}))
        {
            return 269;
        }
        else
        {
            return 223;
        }
    }
};

class Story247 : public Story::Base
{
public:
    Story247()
    {
        ID = 247;

        Text = "You gained the codeword FABRIC.\n\nAzenomei looks different now. His eyes are gold-flecked, and a cast of evil shadows his features. He moves closer with the drowsy menace of a snake. \"So, here I have you at last,\" he murmurs. \"The infamous Shadow is more gullible than I'd have thought.\"\n\n\"What are you talking about?\" you reply angrily. \"You know I'm not the Shadow!\"\n\nHe shakes his head. \"Of course you are. That's why I allowed myself to be caught and put in the oubliette with you. I've pursued you for more than a year. Ever since you stole the gem from my citadel here.\"\n\n\"Gem? What gem? You're talking nonsense. I've never been here before.\"\n\nHe ignores your protests. \"The gem -- a ruby almost as big as the egg of the rokh that perches in its eyrie atop the Isle of Palms -- had been given to me for safekeeping by the King of the Sea. If he learns I have lost it, he will sunder me into atoms and constrain my soul within a sealed copper jar for all time. So, here is your chance to save yourself. Tell me where you hid the ruby.\"\n\n\"For the last time,\" you reply between gritted teeth, \"this is a case of mistaken identity. I never stole anything from you.\"\n\n\"You greedy fool,\" hisses Azenomei, raising his hands to weave a spell. \"Now you will die!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::FABRIC});
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::BLACK_JEWEL}))
        {
            return 293;
        }
        else
        {
            return 315;
        }
    }
};

class Story248 : public Story::Base
{
public:
    Story248()
    {
        ID = 248;

        Image = "images/filler5.png";

        Text = "You know that the rokh's nest lies far beyond the boundaries of the civilized world. If you journey to such remote areas, you might eventually find a clue to its whereabouts. On the other hand, you might just wander fruitlessly for years.";

        Choices.clear();
        Choices.push_back(Choice::Base("Travel to the far east", 180));
        Choices.push_back(Choice::Base("Head west", 271));
        Choices.push_back(Choice::Base("Give up the search for fame and fortune and return to Baghdad", 113));

        Controls = Story::Controls::STANDARD;
    }
};

class Story249 : public Story::Base
{
public:
    std::string PreText = "";

    Story249()
    {
        ID = 249;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You scramble back down, slipping the last few feet to land with a painful jolt.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou are grateful to be back on solid ground. You rack your brains trying to think of another way to reach the nest.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 204; }
};

class Story250 : public Story::Base
{
public:
    std::string PreText = "";

    Story250()
    {
        ID = 250;

        Image = "images/old-man.png";

        Choices.clear();
        Choices.push_back(Choice::Base("Talk to him", 38));
        Choices.push_back(Choice::Base("Ignore him and sit in silence", 61));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Despite your protests, you are dragged in front of the palace gates. The Sultan's executioner was already preparing to execute the captain of the guard, who is relieved to see his men arriving in the nick of time.\n\nThe Sultan looks down from his palanquin. \"Is this the thief?\"\n\nThe captain barely glances at you. \"Yes, O master of justice,\" he says.\n\nThe Sultan orders you to be thrown into prison while he decides your eventual punishment. You are too stunned by the sudden wretched twist of fate to react. ";

        if (Character::VERIFY_ITEMS(player, {Item::Type::BOW}))
        {
            PreText += "Hauled away by guards, you are stripped of your BOW.";

            Character::LOSE_ITEMS(player, {Item::Type::BOW});
        }
        else
        {
            PreText += "You are hauled away by guards.";
        }

        Character::GAIN_MONEY(player, -player.Money);

        PreText += " They also take any money you are carrying, although they leave your other belongings.\n\nThey lower you into an oubliette. The grating drops into place with a harsh clang. You listen in shock as the heavy iron padlock is sealed. You can hear rats rustling through the dank straw carpeting the cell.\n\n\"So you're the jewel thief, then,\" says a voice in the gloom. \"Doesn't look like much to us, eh, Shahrazad?\"\n\nAs your eyes adjust, you make out a figure crouching beside you. He is an old man with limbs as thin and gnarled as twigs. On his lap he has a mangy cat which he is cosseting as though it were a princess.";

        Text = PreText.c_str();
    }
};

class Story251 : public Story::Base
{
public:
    Story251()
    {
        ID = 251;

        Text = "You must present yourself at the palace and request an audience with the Caliph";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::STREETWISE))
        {
            return 68;
        }
        else
        {
            return -1;
        }
    }

    int Continue(Character::Base &player) { return 22; }
};

class Story252 : public Story::Base
{
public:
    Story252()
    {
        ID = 252;

        Image = "images/filler5.png";

        Text = "Sailors pull themselves up through the rigging like monkeys. As the sails catch the wind, your vessel heaves away from the harbour and drifts gracefully downriver towards Basra. The sun rises higher, turning the water from pale gold to a cool, glittering olive-green.\n\nOn the sixth day out, the ship puts in at a village to take on supplies. Strolling through the dusty streets, you soon attract a crowd of children who are eager for you to tell them stories of the splendours of Baghdad. You make up a few tales, but you are overheard by an old man who interrupts, saying, \"These stories are but fiction. It is an elegant tapestry of lore that you spin with your words, but I could tell you a tale that has the golden yarn of truth.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("You are interested in hearing his story", 3));
        Choices.push_back(Choice::Base("Return to the ship", 375));

        Controls = Story::Controls::STANDARD;
    }
};

class Story253 : public Story::Base
{
public:
    Story253()
    {
        ID = 253;

        Text = "The guards raise their swords and come cautiously at you three abreast. Backing away along the landing, you pass a door that must lead up to the palace roof.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go through it", 319));
        Choices.push_back(Choice::Base("Run back the way you came", 341));
        Choices.push_back(Choice::Base("Retreat to the door at the far end of the landing", 363));

        Controls = Story::Controls::STANDARD;
    }
};

class Story254 : public Story::Base
{
public:
    Story254()
    {
        ID = 254;

        Text = "The woman, whose name is Sabira, is grateful to you for rescuing her from her fate. \"To think I might have languished in the Sultan's harem for the rest of my days,\" she says with a grimace as you return to your ship. \"I would sooner have died.\"\n\nYou give her your hand and help her up onto the deck. \"In that case, I may very well have saved your life,\" you point out.\n\nShe looks taken aback, then laughs in delight at your audacity. \"Yes, indeed. And now I shall repay you. Here are two treasures I have had since infancy. The first, given to me by my pious father, is a PRAYER-MAT that always unfurls itself in the direction of Mecca. The second is this BLACK JEWEL, which was my mother's gift. She was superstitious, and this jewel protects against the sorcery of evil wizards, ifrits and the like -- or so I was told.\"\n\nThe captain tells Sabira he will drop her off at the next village.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::PRAYER_MAT, Item::BLACK_JEWEL});
    }

    int Continue(Character::Base &player) { return 375; }
};

class Story255 : public Story::Base
{
public:
    Story255()
    {
        ID = 255;

        Text = "Yussuf is so interested in the murals that he does not see the three iron-masked warriors marching along the gallery towards you. Their swords are burnished like the crescent moon, their robes richly decorated with fine embroidery. But in stark contrast to this artistry are their faces: hideous twisted beast-masks with long metal snouts. The darkness behind their visors drinks up your feeble taper-light.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SWORDPLAY] Draw your SWORD", 278, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::JEWELLED_SWORD}));
        Choices.push_back(Choice::Base("[ARCHERY] Shoot them", 299, Skill::Type::ARCHERY));
        Choices.push_back(Choice::Base("Fight them bare-handed", 321));

        Controls = Story::Controls::STANDARD;
    }
};

class Story256 : public Story::Base
{
public:
    Story256()
    {
        ID = 256;

        Text = "The two of you climb down to the river and swim back to the ship. Later, over supper, Yussuf tells you he is too frightened to claim his share of the treasure. \"You keep both items,\" he says. \"I trust you to use their power for our mutual benefit.\"\n\n\"I shall try to do so,\" you assure him. Although he is not bold, you know him now to be a man of good heart. It may be that his friendship is the greatest treasure you won this evening.\n\nYou gained the codeword GEMINI.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::GEMINI});
    }

    int Continue(Character::Base &player) { return 375; }
};

class Story257 : public Story::Base
{
public:
    Story257()
    {
        ID = 257;

        Image = "images/filler1.png";

        Text = "It is indeed a child -- a pretty little girl whose olive-black eyes are bejewelled with tears. She looks up and gives a woeful sniff when she sees you come in sight. You notice she is clutching a broken garland of violet flowers in her hands. Then you remember that you are still holding the flower the captain plucked.";

        Choices.clear();
        Choices.push_back(Choice::Base("Give it to the child", 323));
        Choices.push_back(Choice::Base("Otherwise", 345));

        Controls = Story::Controls::STANDARD;
    }
};

class Story258 : public Story::Base
{
public:
    Story258()
    {
        ID = 258;

        Text = "Around midnight you are all woken by the lookout. He points with alarm to a group of islanders advancing towards the jetty. The moonlight splashes on their naked knives, their open feral grins.\n\n\"What have you done with our captain, you devils?\" a sailor screams at them, his voice trembling in fright. He turns to you. \"We must storm the headman's house and rescue him!\"\n\nWhatever you think, the decision is out of your hands. The others have already cast off. As the ship drifts out into mid-river, the islanders reach the jetty. In their midst is a withered old man with a skull-topped staff. He begins a low howling chant that reverberates off the hills. The sound of it prickles the hair of your scalp. You are sure it is a baneful spell.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::MAGIC))
        {
            return 324;
        }
        else
        {
            return 346;
        }
    }
};

class Story259 : public Story::Base
{
public:
    Story259()
    {
        ID = 259;

        Text = "How will you attack?";

        Choices.clear();
        Choices.push_back(Choice::Base("[SWORDPLAY] Use a SWORD", 347, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::JEWELLED_SWORD}));
        Choices.push_back(Choice::Base("You do not possess a SWORD or do not wish to use it", 304));

        Controls = Story::Controls::STANDARD;
    }
};

class Story260 : public Story::Base
{
public:
    std::string PreText = "";

    Story260()
    {
        ID = 260;

        Bye = "The next morning, shivering and hungry, you make your way down out of the hills to fetch the others.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The sky is like diamond, displaying the stars with dazzling clarity. A wind begins to blow in from the east and the temperature drops. Without so much as a blanket, you are forced to shelter against the bare rocks. A little bracken is all the cover you can find.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            Character::GAIN_LIFE(player, -1);

            PreText += "\n\nYou LOSE 1 Life Point.";
        }
        else
        {
            PreText += "\n\n[WILDERNESS LORE] You are used to this kind of hardship.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 289; }
};

class Story261 : public Story::Base
{
public:
    Story261()
    {
        ID = 261;

        Text = "The slave master is a short bullish man with a wide witless grin. He chains you to the oars and advises you not to try to escape. \"I'm telling you this for your own good,\" he says as he walks off.\n\nThat night you pick the lock and slip out of your shackles. Rousing each of the other slaves in turn, you press your hand to their lips while you get them free.\n\n\"Are we escaping?\" whispers one. \"Where shall we go?\"\n\n\"You can all go where you like, as long as it's in a different direction from me.\"\n\nOne at a time, the slaves drop over the side and swim for the river bank. You are the last to go. Freeing the others was a sensible precaution in case the ship's captain is a vindictive man. If you had escaped alone he might have hired thugs to pursue you, but this way you cover your tracks by flooding the countryside with runaway slaves. It is a case of doing well while doing good.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::MORDANT);
    }

    int Continue(Character::Base &player) { return 215; }
};

class Story262 : public Story::Base
{
public:
    Story262()
    {
        ID = 262;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            return 307;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::ARCHERY))
        {
            return 329;
        }
        else
        {
            return 351;
        }
    }
};

class Story263 : public Story::Base
{
public:
    Story263()
    {
        ID = 263;

        Image = "images/filler2.png";

        Text = "Scooping the sand away from the pole, you uncover a stretched piece of camel leather. When this is removed, water trickles forth from a hidden well. There is not much, but enough to clear the clogging sand from your mouth and fill your limp waterskins.\n\nYou are careful to replace the leather so that other travellers will also find water here. \"In the face of the desert's callous ways, all men are brothers,\" remarks Hakim, adding a short prayer of thanks before signalling for the caravan to move on.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 308; }
};

class Story264 : public Story::Base
{
public:
    std::string PreText = "";

    Story264()
    {
        ID = 264;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The others start to scatter, utterly routed by the Bedouin's show of fury, leaving you alone to confront the foe.\n\nThe Bedouin chief is first to reach you. Dashing his spear-thrust aside, you give him a punishing blow as he goes hurtling past. But although you hear him gasp aloud in pain, he refuses to retreat. He wheels his camel around, and now the other Bedouin are also upon you.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -3;

            PreText += "[SWORDPLAY] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        if (player.Life > 0)
        {
            PreText += "\n\nYour bravery rallies the others, who come racing back to join the fight. At last the Bedouin lie dead on the sun- baked ground and you are able to loot their belongings.\n\nHakim presents you with 10 dinars as a reward.";

            Character::GAIN_MONEY(player, 10);
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::MORDANT}))
        {
            return 67;
        }
        else
        {
            return 218;
        }
    }
};

class Story265 : public Story::Base
{
public:
    Story265()
    {
        ID = 265;

        Text = "Falling into an easy rhythm, you manage to evade blow after blow. The Lord of the Desert's sword sweeps down again and again, never quite able to find its mark. A mystical sense of tranquillity comes over you, and you move as though in a trance. Everything seems unreal. The sight of the Lord of the Desert's glaring gaze no longer fills you with terror. You now see the unearthly beauty of the scene: the shimmering colours of the silk tapestries, like streams of spring water...\n\nThe heady odour of perfume and incense...\n\nThe lustrous sheen of gold and jewels...";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 152; }
};

class Story266 : public Story::Base
{
public:
    Story266()
    {
        ID = 266;

        Text = "The ship veers away from the coast. You watch with sinking heart as all sight of land vanishes in the distance. Soon your misery turns to despair, because the clouds ahead are as thick and dark as soot, and the hissing crack of lightning rolls across the sky. The sea seethes, pitch-black chopped through by crests of angry white foam.\n\nAs the clouds descend to cover you, the wind strikes with gale force, ripping at the furled sails. The ship pitches over, forcing you to cling to the mast. Waves leap like capering demons over the bows. Sea water sloshes around your feet. The rain falls as hard and heavy as a curtain of ice.\n\nEven over the roar of the storm, you hear the great dolorous crack as the mainmast splits. It falls across the deck, sundering the spliced timbers, pulling the ship in half. You plunge into the sea, fingers scrabbling desperately to hold onto a broken plank. Water closes over your head, wrapping you in warm silent darkness.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 280; }
};

class Story267 : public Story::Base
{
public:
    Story267()
    {
        ID = 267;

        Text = "You will have to try another tack.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try [CUNNING]", 333, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Sneak off using the LAMP of Antar", 495, {Item::LAMP_OF_ANTAR}));
        Choices.push_back(Choice::Base("Attack the shark men", 108));
        Choices.push_back(Choice::Base("Wait and see what the dwarf does when he wakes up", 397));

        Controls = Story::Controls::STANDARD;
    }
};

class Story268 : public Story::Base
{
public:
    Story268()
    {
        ID = 268;

        Text = "The Sultan starts to remove his mask. In the space of one heartbeat you have drawn an arrow and nocked it to your bowstring. In another, you've raised the bow and sent the shaft speeding across the clearing. It strikes the Sultan through the eye, pinning the mask to his face.\n\nThe three knights give a gasp and reach for their swords. You ready another arrow. \"The duel was fairly fought and won,\" you say to them. \"Take your master's body and go. If you're of a mind to argue, I have three more arrows I can spare.\"\n\nPutting the Sultan's body across his horse, the knights lead it away. As you cross the clearing, you find a BLACK JEWEL lying among the fallen leaves.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::BLACK_JEWEL};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story269 : public Story::Base
{
public:
    Story269()
    {
        ID = 269;

        Text = "\"Shall I transform you back to human form?\" asks the jinni. You try to reply. It just comes out as a hiss.\n\nThe jinni leans closer, smiles a mocking smile. \"No? You wish to remain a snake?\"\n\nYou try to bite him, but your fangs close on a thin wisp of acrid smoke.\n\n\"You must enjoy being a snake!\" he says. \"You've taken to it very quickly. Well, if you don't have any more use for me, I'll be off.\"\n\nHe flits up into the sky and is lost among the stars. You have only yourself to blame. The jinni returned treachery for treachery. You will spend the rest of your life in the body of a snake.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story270 : public Story::Base
{
public:
    std::string PreText = "";

    Story270()
    {
        ID = 270;

        Choices.clear();
        Choices.push_back(Choice::Base("Break the door down", 300));
        Choices.push_back(Choice::Base("Go looking for Azenomei", 224));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Azenomei leads you into the wasteland, where the hot air rasps your throat and each footstep raises a cloud of acrid dust. For days you travel without seeing any sign of life. From dawn to dusk you feel as though your flesh is being dried on your bones. Night makes the rocks colder than ice.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE) && !Character::VERIFY_ITEMS(player, {Item::Type::WATER_BOTTLE}))
        {
            Character::GAIN_LIFE(player, -2);

            PreText += "\n\nYou LOSE 2 Life Points.";
        }
        else
        {
            if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
            {
                Character::EMPTY(player, Item::Type::WATER_BOTTLE);

                PreText += "\n\nThe WATER BOTTLE is now EMPTY.";
            }
        }

        if (player.Life > 0)
        {
            PreText += "\n\nYou see a gleam of burnished metal in the thickening dusk. \"It is the jinni's citadel,\" breathes Azenomei. Taking your arm, he hurries on until you stand below the walls. The battlements and turrets are all of polished bronze, flickering like fire in the red sunset.\n\nYou find the doors -- a huge double portal of ebony studded with iron. Putting your shoulders against the doors, you slowly push them open. Beyond lies a great hall with many passages leading off it.\n\n\"Let's split up and look for my sister,\" says Azenomei. \"We'll have to hurry, because the jinni might return at any moment.\"\n\nYou gaze along the hall. \"But there may be hundreds of rooms in the citadel. How will we find her?\"\n\n\"There are a thousand doors,\" says Azenomei, starting off down one of the passages. \"Just be sure not to try and open any that are locked.\"\n\nChoosing a passage at random, you start to explore. Doorway after doorway leads to empty rooms. At last you find a door that will not open. You thought there was a muffled shout from the other side, but when you press your ear to the door you can hear nothing.";
        }

        Text = PreText.c_str();
    }
};

class Story271 : public Story::Base
{
public:
    Story271()
    {
        ID = 271;

        Text = "You travel in the far west, through the inhospitable hinterland of Egypt where, so the saying goes, 'only God and the wind dwell.'\n\nSome legends place the nest of the rokh at the head of the River Nile. You trudge up into the mountains until you have left the last scattered settlements far behind. The landscape is one of soaring desolate crags under a sky filled with the constant threat of storms.\n\nWater is hard to come by, and the only things to eat are snakes and insects. You climb a slope of loose dark pebbles, passing a stream where you drink deeply despite the salty taste of the water. Suddenly a boom shakes the ground. At first you think it is thunder, but then you see a corona of hissing flame against the mountain peak. A cloud of hazy black smoke is rolling down the slope towards you. You are on an erupting volcano!";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            Choices.push_back(Choice::Base("Run for your life", 487));
            Choices.push_back(Choice::Base("Look for shelter", 90));
        }
    }

    int Continue(Character::Base &player) { return 44; }
};

class Story272 : public Story::Base
{
public:
    Story272()
    {
        ID = 272;

        Text = "You manage to climb just a little further, until you reach a cloud streaming like a banner beside the pinnacle. Leaping onto the cloud, you wait for it to drift up, carrying you miraculously to the rokh's nest at the top.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 325; }
};

class Story273 : public Story::Base
{
public:
    Story273()
    {
        ID = 273;

        Text = "As Jafar makes his throw, you sweep the CLOAK around, sweeping the deadly blade out of the air before it reaches its target.\n\nThe Caliph, recovering from his shock, calls for his guards. Jafar turns and flees.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 339; }
};

class Story274 : public Story::Base
{
public:
    Story274()
    {
        ID = 274;

        Text = "The sailors move like monkeys through the rigging. The sails billow as they catch the wind, and your vessel moves out from the dock and drifts gracefully downriver towards Basra. In the dawn the water is splashed with light like liquid gold. It flows sluggishly past as the day wears on, dark and deep as a draft of cool wine.\n\nA week passes. Moored one night in midstream, you find yourself unable to sleep. Climbing quietly over the dozing forms of your fellow sailors, you look out from the rail. The sky is filled with stars, and the moon watches its twin in the dim black depths of the river. You hear the soft plash of oars and, gazing upriver, you see the lamps of a barque approaching.";

        Choices.clear();
        Choices.push_back(Choice::Base("Wake the captain", 26));
        Choices.push_back(Choice::Base("Wait and watch", 48));

        Controls = Story::Controls::STANDARD;
    }
};

class Story275 : public Story::Base
{
public:
    Story275()
    {
        ID = 275;

        Image = "images/flying-carpet.png";

        Text = "Casting the limp carcass of the demon to one side, you race across the parade ground in search of Jafar. He can't have got far, the fat waddling toad. Then you see him, crouching by the wall as he unrolls a long carpet embroidered with mystic sigils.\n\nHe looks up, shakes his head with mock pity, and steps onto the carpet. \"Too late,\" he calls. \"But don't worry. I'll make sure our paths cross again.\"\n\nSo saying, he gives an imperious gesture and the carpet starts to rise from the ground. As it rises, your heart sinks. You can't possibly get to Jafar before he is out of reach.\n\nThere is a crack like wood being hit with a hammer. One of the stable doors flies open and bangs against the wall. You see Jafar's head shoot round in astonishment, and you follow his gaze to see your white stallion Antar rearing fiercely in the open doorway. With a proud whinny, he gallops over and you pull yourself up by his mane.\n\nTo the end of your days, you will never quite be sure of what happens next. You could have sworn Antar's hoofs strike sparks off thin air as, with a breathtaking leap, he carries you up beside Jafar on the flying carpet.\n\nJafar's mouth drops open -- whether to cast a spell or simply to curse you, you will never know. Antar rears, plunges, and clubs him with his hoof. Jafar topples and falls, and the carpet slowly drifts back to the ground. Dismounting, you lift Jafar's wrist and search for a pulse. Nothing. The traitor is dead.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::IRIS}))
        {
            return 403;
        }
        else
        {
            return 120;
        }
    }
};

class Story276 : public Story::Base
{
public:
    Story276()
    {
        ID = 276;

        Text = "Against a true master of the sword such as Masrur, even a skilled fighter like yourself can have no chance. He calmly parries your barrage of desperate attacks. Toying with you, he allows his sword- point to prick your skin again and again -- painful but not mortal wounds.\n\nYou LOSE 1 Life Point.";

        Bye = "Finally tiring of this sadistic sport, Masrur disarms you with a deft twist of his blade.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 2; }
};

class Story277 : public Story::Base
{
public:
    Story277()
    {
        ID = 277;

        Text = "Having dealt with the guards, you push aside the curtain of the kiosk. The woman presses back on her cushions, frightened by the carnage she has just witnessed, but you reach out a reassuring hand. \"Have no fear of me, my lady,\" you say to her with a smile.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 254; }
};

class Story278 : public Story::Base
{
public:
    Story278()
    {
        ID = 278;

        Image = "images/filler1.png";

        Text = "The first warrior steps forward, making no attempt to parry your attack. Your blade drives deep through the folds of his cloak, piercing his heart, but he makes no sound. Withdrawing the sword, you wait for him to topple. You are taken by surprise when, instead, he lunges at your throat. You barely deflect the blow, and now you notice that there is no trace of blood on your sword. These warriors are immune to the touch of cold steel!\n\nHis next blow is luckier -- or perhaps your timing is off. The edge of his scimitar strokes the flesh of your upper arm, drawing a deep line of scarlet.\n\nYou LOSE 2 Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use a CLOAK", 343, {Item::CLOAK}));
        Choices.push_back(Choice::Base("Drop your SWORD and fight empty-handed", 321));
        Choices.push_back(Choice::Base("Try to break away and retreat through the caves", 365));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }
};

class Story279 : public Story::Base
{
public:
    Story279()
    {
        ID = 279;

        Text = "A man makes the sign of protection against the evil eye as you pass him on a street corner. You look at him in surprise and start to ask why he acted as he did, but he shuns you, saying, \"O unlucky one!\"\n\nDumbfounded, you watch as he hurries off along the street.";

        Choices.clear();
        Choices.push_back(Choice::Base("Follow him", 322));
        Choices.push_back(Choice::Base("Return to the ship", 301));

        Controls = Story::Controls::STANDARD;
    }
};

class Story280 : public Story::Base
{
public:
    Story280()
    {
        ID = 280;

        Image = "images/filler3.png";

        Text = "The surf pounds an accompaniment to your throbbing head. There is wet sand under your face. A crab is pinching your finger with its claws. You shake it off and sit up. You are on a lonely beach backed by high cliffs that shine with veins of blue and green rock. You realize you must have passed out. Getting shakily to your feet, you stagger along the beach.\n\nSick and dazed as you are, your first glimpse of the palace seems like a hallucination. It rises from a tumble of rocks at the end of the beach. Needle-thin spires of white marble rise around domes crusted with pastel mosaic. You stand in awe as figures emerge from the buildings and come to greet you. They are men and women with faces like angels. You swoon into their arms and feel them carry you to the palace, where you are laid on a soft silken bed. Gratefully, you sleep.\n\nThe next time you awaken, it is to see the faces of ordinary men -- honest sailors, by the look of them. They are clustered around your bed. \"What happened to the others?\" you say, sitting up.\n\nOne of the sailors steps forward. His accent tells you he is from Basra. \"The wizard's beautiful servants, you mean? I saw them once. We all did, when we first arrived here.\"\n\nYou swing your legs to the floor and test your strength. You feel fully recovered. \"What wizard?\" you ask as you get to your feet. \"Are we his prisoners?\"\n\nThey all laugh at this. \"No, we're his guests!\" says the man from Basra. \"He saved us all when a giant fish swallowed our ship. He even gave us a new ship to journey home, but he told us we had to wait a week because he had seen in the future that another castaway would be swept up on the shore. We've been waiting for you.\"\n\nYou notice that all your belongings are neatly piled beside the bed. Your money is there too. Your mysterious benefactor apparently has only the best of intentions -- unlike most of the wizards you've heard of.\n\n\"Now that you're fully recovered,\" says one of the other sailors, \"why delay any longer? Let's set sail.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Go with them to their ship right away", 389));
        Choices.push_back(Choice::Base("Ask them to wait while you go to speak with the wizard", 444));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.Life = player.MAX_LIFE_LIMIT;
    }
};

class Story281 : public Story::Base
{
public:
    Story281()
    {
        ID = 281;

        Text = "You press yourself to one side of the doorway and listen. Inside, you hear two men talking. From the strained way they're speaking, you guess they must be carrying something heavy. Risking a quick peek around the door-frame, you see them manhandling a long rolled-up rug through into the room beyond.\n\n\"I think great-grandfather's put on weight,\" grumbles one of the men.\n\n\"Sssh! He'll hear you,\" says the other. He leans against the wall to wipe a trickle of sweat off his forehead. \"Just one more of these to go, thank goodness. I think it's old Bamara's great uncle.\"\n\nThe other glances back. You hastily duck out of sight, but he wasn't looking in your direction. He takes an appraising glance at another rug lying rolled up on the floorboards. \"No,\" he mutters thoughtfully. \"We took him in first, remember?\"\n\nThey disappear through into the next room. This is your chance. Scuttling in, you race across to the inner doorway and glance through. You get a quick impression of a crowd of people crouching in near-darkness. Looking back around the vestibule, your gaze falls on the rolled-up rug. The two men will be back for it in less than a minute.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take a closer look at it in the meantime", 411));
        Choices.push_back(Choice::Base("Creep quietly into the next room", 433));
        Choices.push_back(Choice::Base("Enter boldly and announce yourself", 8));
        Choices.push_back(Choice::Base("Sneak back to the ship", 258));

        Controls = Story::Controls::STANDARD;
    }
};

class Story282 : public Story::Base
{
public:
    std::string PreText = "";

    Story282()
    {
        ID = 282;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Both guards strike at the same time, driving towards you from either side with straight thrusts of their long knives.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            PreText += "\n\nYou are pierced by the tips of both blades. You LOSE 2 Life Points.";

            Character::GAIN_LIFE(player, -2);
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 369;
        }
        else
        {
            return 390;
        }
    }
};

class Story283 : public Story::Base
{
public:
    Story283()
    {
        ID = 283;

        Text = "You have heard the story of this island. Long ago, an old woman who could have no children found two eggs buried in the ground. One hatched, and she dressed the little manikin that emerged in baby's clothing. He grew to become a strange dwarf with magical powers, and one of his feats was to build a high tower in the space of a single night. In this tower he placed the other egg, because he had learned from a prophecy that in that egg slept his brother, whom he feared.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 311; }
};

class Story284 : public Story::Base
{
public:
    Story284()
    {
        ID = 284;

        Image = "images/filler5.png";

        Text = "You say your farewells to Hakim and the others. Many speak to you with tremors in their voices, and several openly wipe away tears. Though you met as strangers and it is likely you'll never see any of them again, you have shared experiences that make you all as close as cousins.\n\nHakim himself presses a pouch into your hand. \"You've been more help than I could have imagined,\" he says. \"Take this as a little bonus.\"\n\nOnce out of sight around the corner, you check the contents of the pouch: 3 dinars. Well, for Hakim that is generous.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 3);
    }

    int Continue(Character::Base &player) { return 215; }
};

class Story285 : public Story::Base
{
public:
    Story285()
    {
        ID = 285;

        Text = "The pirates sail away after looting the merchant ship of its cargo. You can hear their merry shouts from afar as they broach one of the wine barrels.\n\n\"They can't be true believers,\" says the captain of marines with a sorry shake of his head. \"Don't they know of the Prophet's warning against drunkenness?\"\n\nSeveral of his men sidle away rather guiltily when they hear this. Your reply is more forthright. \"Much worse than drunkards, they are thieves and murderers. Tonight, in any case, they'll be held to account for all their crimes.\"\n\nYou may have spoken too soon. The pirate ship is faster than your own, and soon their black sails drop out of sight across the waves. A few minutes later, the lookout calls down that he has lost them altogether.\n\nThe marine captain smacks his fist into his palm. \"Two tons of camel dung!\" he swears extravagantly. \"We'll never find them now.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::HAWK}))
        {
            return 486;
        }
        else if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::LUCK, Skill::Type::SEAFARING}))
        {
            return 393;
        }
        else
        {
            return 415;
        }
    }
};

class Story286 : public Story::Base
{
public:
    Story286()
    {
        ID = 286;

        Text = "By evening, when it is time to halt and rest, you are close to fainting from thirst and weariness. You drop to your haunches on the ground, too weak even to eat. Others are faring even worse. One old man -- a slave of Hakim's -- is shivering with the first signs of fever.\n\nYou LOSE 1 Life Point.";

        Bye = "You survive to see the sunrise.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 308; }
};

class Story287 : public Story::Base
{
public:
    Story287()
    {
        ID = 287;

        Text = "You have heard tales of the Lord of the Desert. He is one of the powerful spirits that men used to worship in the days before the coming of the Prophet. His nature is such that he uses a victim's own strength against them. In the legends, the more a person strove to defy the Lord of the Desert, the easier they made it for him to overcome them.\n\nYou also recognize the glyph in the keystone above the alcove. It is the seal of Suleiman, the wizard king whom all evil spirits feared. For all his power, the Lord of the Desert could never pass beyond that magic glyph.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 309; }
};

class Story288 : public Story::Base
{
public:
    Story288()
    {
        ID = 288;

        Text = "Seeing an opening, you jab your elbow into the base of his throat. He snarls like a dust devil and slashes his sword across your forearm, drawing a gout of blood. You can feel yourself weakening now.\n\nYou LOSE 2 Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go for a punch", 468));
        Choices.push_back(Choice::Base("Go for a kick", 242));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }
};

class Story289 : public Story::Base
{
public:
    Story289()
    {
        ID = 289;

        Text = "The caravan travels on along roads that get increasingly busy as you approach Cairo. Porters carrying great bundles of grain and cloth jostle outside the city gates in a press of heavily laden camels, donkeys and rumbling wheeled carts.\n\nIn all the confusion, it amazes you that Hakim somehow manages to squeeze his way to the front of the crowd and present his papers to the sentries. The papers themselves are just a formality, since probably neither Hakim nor the sentry he speaks to can read. The important thing is the bag of gold coins that is discreetly handed over. With this transaction complete, the sentries help to push the crowd aside so that your camels can traipse through into the city.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::MORDANT}))
        {
            return 192;
        }
        else
        {
            return 284;
        }
    }
};

class Story290 : public Story::Base
{
public:
    Story290()
    {
        ID = 290;

        Text = "The warmth of your touch is enough to crack the egg. A tiny figure jumps out, growing in seconds into the identical twin of the sleeping dwarf. Then you see on second glance that they are not identical. This dwarf has a full friendly smile in place of the other's prim little smirk.\n\n\"For a hundred years I've waited in that egg,\" he says. \"I knew of my brother's evil deeds, which came to me in dreams, but I was powerless to act. Now I have been hatched into this world. It is time to set matters straight.\"\n\nWith a wave of his hands, he transports you and the others back to the ship. \"You are free to go,\" he says. \"I'll deal with my wicked twin.\" With that, he vanishes again in a blaze of light.\n\nYou find that all your wounds are healed.\n\nCaptain Ibrahim loses no time giving the order to weigh anchor. The mysterious island drops astern and is lost to sight.\n\nThe next few days pass uneventfully. You have not spotted any other vessels until a ship drifts into view one afternoon. Her sails are furled and there is no reply to your shouts. As you come alongside, you see the reason. The deck is strewn with corpses.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.Life = player.MAX_LIFE_LIMIT;
    }

    int Continue(Character::Base &player) { return 356; }
};

class Story291 : public Story::Base
{
public:
    Story291()
    {
        ID = 291;

        Text = "As the Sultan removes his mask, there is a moment when it obscures his gaze. Leaping forward, you press the mirror up in front of him. He stares into it. There is a gasp and he claws at his eyes, then slumps forward dead at your feet.\n\nThe three knights step closer, watching you warily. They are frightened of whatever magic you might use against them. Silently they retrieve the body, placing it across their master's horse before withdrawing in confusion. You are left alone in the woods.\n\nThere is nothing you can do for your friends, but at least you were able to avenge them. As you go to leave, you notice a BLACK JEWEL lying on the moss by your feet.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::BLACK_JEWEL};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story292 : public Story::Base
{
public:
    Story292()
    {
        ID = 292;

        Text = "You wait until midnight when everyone else is asleep. The ROPE uncoils like a serpent, stretching up into the air until it reaches the bars of the grille.\n\nAzenomei climbs up first, trying each of keys until he finds one that fits. The padlock springs open and the two of you emerge into the sweet fresh air.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 358; }
};

class Story293 : public Story::Base
{
public:
    Story293()
    {
        ID = 293;

        Text = "Cold tongues of magical flame blast from his fingers to lick around you. The JEWEL absorbs the brunt of the spell but is destroyed in the process.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::BLACK_JEWEL});

        Choices.clear();

        if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAREM}))
        {
            Choices.push_back(Choice::Base("Use [MAGIC]", 359, Skill::Type::MAGIC));
            Choices.push_back(Choice::Base("Use the Jericho HORN", 381, {Item::JERICHO_HORN}));
            Choices.push_back(Choice::Base("Fight", 410));
        }
    }

    int Continue(Character::Base &player) { return 337; }
};

class Story294 : public Story::Base
{
public:
    std::string PreText = "";

    Story294()
    {
        ID = 294;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        Type = Story::Type::NORMAL;

        PreText = "No way to go on and no way back. You cling miserably to the sheer cliff and desperately try to think of a plan.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::LUCK) && !Character::VERIFY_ITEMS_ANY(player, {Item::MAGIC_SLIPPERS, Item::INDIAN_ROPE}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nYou finally cannot hang on any longer, and with a bleak cry you go plunging to your doom.";
        }
        else
        {
            if (!Character::VERIFY_SKILL(player, Skill::Type::LUCK))
            {
                Choices.push_back(Choice::Base("Use a pair of MAGIC SLIPPERS", 338, {Item::MAGIC_SLIPPERS}));
                Choices.push_back(Choice::Base("Use an INDIAN ROPE", 360, {Item::INDIAN_ROPE}));
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 157; }
};

class Story295 : public Story::Base
{
public:
    std::string PreText = "";

    Story295()
    {
        ID = 295;

        Bye = "Jafar sees his last attempt has failed and, cursing, he turns to run.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You step forward just as Jafar throws the knife. Instead of hitting the Caliph, it impales itself in your shoulder. Immediately you feel a wave of deathly weakness as the poison takes effect.";

        if (!Character::VERIFY_ITEMS(player, {Item::Type::ANTIDOTE}))
        {
            Character::GAIN_LIFE(player, -5);

            PreText += "\n\nYou LOSE 5 Life Points.";
        }
        else
        {
            PreText += "\n\n[Item: ANTIDOTE] You take the ANTIDOTE to counteract the poison.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 339; }
};

class Story296 : public Story::Base
{
public:
    Story296()
    {
        ID = 296;

        Text = "For the first week you have nothing to do but walk along beside the camels and steady the swaying bundles on their backs. At Kermanshah, a town in the foothills, Abdullah exchanges the camels for donkeys. When he unwraps the bundles, you are astonished to see that they are just rags.\n\n\"Is your head on backwards?\" you ask him. \"You cannot think they'll pay you much for those in the east.\"\n\n\"Trade is not my true mission,\" he reveals. \"Stitched inside these bundles are secret messages that the Caliph has told me to deliver to the commanders of his forts beyond the mountains.\" He peers hard at you. \"Breathe no word of this to another, as you value your life.\"\n\nYou do not need to be told twice. The next day you start your ascent into the mountains, guiding the donkeys up steep flinty paths until you reach a brooding forest. The slanting rays of the sun hang in the misty air, against which the shadows of the leaves remind you of naked blades.\n\nA gazelle comes racing through the trees. You hear the pounding of hoofs and realize that it is being hunted, but before you can say anything one of the donkey-handlers has brought the gazelle down with his own spear. \"We'll eat well tonight!\" he calls merrily to the others.\n\nYou look up. Against the backdrop of mist, four armed riders take ominous shape between the trees.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hide", 312));
        Choices.push_back(Choice::Base("Wait to see what they want", 125));

        Controls = Story::Controls::STANDARD;
    }
};

class Story297 : public Story::Base
{
public:
    Story297()
    {
        ID = 297;

        Text = "You are amazed at Masrur's strength and skill. He is one of the most dangerous swordsmen in the world, and in his youth he must have been unbeatable. As it is, your best manoeuvres and parries are only just enough to keep him at bay. You know your only hope is to stay out of his reach and let him tire himself out.\n\nYou glance aside to judge the distance to the door. Taking instant advantage of your lapse of concentration, Masrur breaks through your guard and his sword lays open a long gash across your brow. You stagger back, wiping the blood from your eyes, expecting the death-blow to follow at any moment. But by this time Masrur's age and bulk are beginning to tell. Leaning on his sword to get his breath back, he gasps, \"You're better than I thought... you wretch... But I'll have you now...\"\n\nThe door to the landing is behind you. As Masrur lumbers forward, you get ready to time your dodge perfectly. So that he doesn't realize what you're planning, you taunt him by saying, \"You should stick to your job as executioner, Masrur. You don't seem so hot when you're fighting someone who isn't tied up.\"\n\nThat does it. He snarls like a lion and lunges for your heart.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 70; }
};

class Story298 : public Story::Base
{
public:
    Story298()
    {
        ID = 298;

        Text = "She explains her plan: \"We'll exchange clothes. I can slip away back to your vessel, you stay here in my place.\"\n\nYou give her a doubtful frown. \"I think I see a flaw. Doesn't that leave me on my way to become an inmate of the harem?\"\n\nShe stifles a musical trill of laughter. \"Please excuse me for pointing this out,\" she says between chuckles, \"but the guards will let you go as soon as they get a good look at you. Not that your looks are unappealing, you understand, but you just don't have the elegance that marks out a good concubine.\"\n\nProbably she's right, but do you want to risk it? If her plan backfires you might spend the rest of your days in the Sultan's harem.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go along with the plan", 385));
        Choices.push_back(Choice::Base("Resort to [CUNNING]", 342, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Attack the guards", 320));
        Choices.push_back(Choice::Base("Forget about helping the woman and return to your ship", 375));

        Controls = Story::Controls::STANDARD;
    }
};

class Story299 : public Story::Base
{
public:
    Story299()
    {
        ID = 299;

        Text = "The arrow lances through the air, finding its mark in the first warrior's heart. But he gives no grunt of pain, nor does he sway and fall. Instead he plucks out the shaft and regards it for a moment as though he had never seen such a thing before. Breath rasps contemptuously behind the iron plate of his helmet as he tosses the arrow aside and lunges forward. His moon-sliver sword gives your shoulder a lusty bite, and blood streams freely from the wound as he steps back with a flourish.\n\nYou LOSE 2 Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Draw a SWORD", 278, Choice::Type::ANY_ITEM, {Item::SWORD, Item::JEWELLED_SWORD}));
        Choices.push_back(Choice::Base("Launch yourself at them and fight bare handed", 321));
        Choices.push_back(Choice::Base("Make a run for it", 365));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }
};

class Story300 : public Story::Base
{
public:
    Story300()
    {
        ID = 300;

        Image = "images/ayisha.png";

        Text = "The door frame splinters under the force of a kick, and you step through into a scented chamber curtained with diaphanous silks. A raven-haired girl reclines on a golden couch in the middle of the room. She looks up as you enter, and her expression is a mixture of fear and hope as she says, \"Have you come to free me?\"\n\nYou notice that her ankle is chained to the floor, the chain being fixed by a huge padlock. \"Who are you?\" you ask.\n\n\"Ayisha, the daughter of the Caliph. I was stolen from Baghdad in the middle of the night by a powerful jinni who brought me here to his citadel.\"\n\nYou go closer and test the strength of the padlock. It is easy to see that you could never hope to break it. \"Perhaps Azenomei has a key to fit it.\"\n\n\"Who is Azenomei?\"\n\n\"I am.\"\n\nYou turn to see your friend standing in the doorway. He slowly runs his hand over the broken wood and then shakes his head regretfully. \"I did tell you not to open any locked doors.\"\n\n\"Azenomei...\" You take a pace towards him. \"Look, I've found your sister.\"\n\nHis only answer is a soft mocking laugh. After a moment, Ayisha says, \"He lied to you. He isn't my brother. This is the jinni who abducted me!\"\n\nYou gained the codeword HAREM.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::HAREM});
    }

    int Continue(Character::Base &player) { return 247; }
};

class Story301 : public Story::Base
{
public:
    Story301()
    {
        ID = 301;

        Text = "Where are you headed?";

        Choices.clear();
        Choices.push_back(Choice::Base("You are bound for Egypt", 409));
        Choices.push_back(Choice::Base("You are bound for the Indies", 431));
        Choices.push_back(Choice::Base("You are heading towards the Scarlet Isle", 451));
        Choices.push_back(Choice::Base("You cannot remember", 466));

        Controls = Story::Controls::STANDARD;
    }
};

class Story302 : public Story::Base
{
public:
    Story302()
    {
        ID = 302;

        Text = "The city is a sight to take the breath away. Columns of ivory and alabaster support walls of pure shimmering gold. The blocks of the pavement are gold and silver inlaid with sparkling jewels. The minarets are encrusted with lapis lazuli of so intense a blue that they seem as though the sky itself has taken on solid form.\n\nAwestruck, you pass through a burnished arch that gleams like flame in the sunlight and enter a wide hall where a strange battle is taking place. A gryphon -- a lion-like being with an eagle's wings and beak -- is struggling with a giant scorpion. The fury of their battle is like nothing you have ever witnessed. Their deafening cries reverberate off the walls: the shriek and caw of the noble gryphon, the awful rattling hiss of its venomous foe. Each blow makes the metallic floor ring like an anvil. The whole chamber is awash with gore.\n\nDuring a respite in the fighting, the gryphon falls back, sinking to the floor beside you. The scorpion crouches against the far wall. It is injured too, but you see that it is recovering its strength faster. As the scorpion advances flailing its poison-coated sting, the gryphon turns to you and says weakly, \"Grant me a drop of your blood. It is the only thing that will sustain me in this battle.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("You consent to give some of your blood", 452));
        Choices.push_back(Choice::Base("Otherwise", 402));
        Controls = Story::Controls::STANDARD;
    }
};

class Story303 : public Story::Base
{
public:
    Story303()
    {
        ID = 303;

        Text = "If you had hoped for a magic lamp or a cask of jewels, you are due for disappointment. The metallic glint turns out to be just a single dinar buried in the muck at the bottom of the well. As you rub it clean and drop it into your pocket, you notice a narrow tunnel leading off from the well shaft. Looking along it, you can see nothing but dank walls with darkness stretching beyond.";

        Choices.clear();
        Choices.push_back(Choice::Base("Follow the tunnel to see where it leads", 225));
        Choices.push_back(Choice::Base("Climb back out of the well and return to the ship", 189));
        Choices.push_back(Choice::Base("Go to the headman's house", 235));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 1);
    }
};

class Story304 : public Story::Base
{
public:
    Story304()
    {
        ID = 304;

        Text = "You jump forward with a sharp yell, but your opponent is not intimidated. He holds you off long enough for the other guard to slash a deep cut in your flank.\n\nYou LOSE 1 Life Point.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 282; }
};

class Story305 : public Story::Base
{
public:
    std::string PreText = "";

    Story305()
    {
        ID = 305;

        Choices.clear();
        Choices.push_back(Choice::Base("Strike at her with your bare fists", 413));
        Choices.push_back(Choice::Base("Strike at her with a SWORD", 391, Choice::Type::ANY_ITEM, {Item::SWORD, Item::JEWELLED_SWORD}));
        Choices.push_back(Choice::Base("Look around for a weapon", 435));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The two male ghouls are as large as bulls standing on their hind legs. They are a lot uglier, of course. Uttering howls to make your blood flow like ice water, they launch iron-hard kicks at your shins while shredding at your face with their long talons.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -4;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        if (player.Life > 0)
        {
            PreText += "\n\nYou step forward over the fallen bodies of the brothers. You spare no pity for the likes of them -- they were mere beasts who lived by preying on blameless travellers. But your real wrath is reserved for their evil dam, the vulture-faced crone who now stands spitting and snarling before you. You will take pleasure in ridding Creation of her loathsome life.\n\nSeeing you to be a doughty fighter, she makes a lunge towards a cleaver hanging on the wall.";
        }

        Text = PreText.c_str();
    }
};

class Story306 : public Story::Base
{
public:
    Story306()
    {
        ID = 306;

        Text = "You believe you can come up with a plan to catch the Red Sea pirates. The problem is, who's going to listen to an impoverished wanderer like you?";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [SEAFARING]", 371, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("Use [STREETWISE]", 392, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("Use a HAREM COSTUME", 418, {Item::HAREM_COSTUME}));
        Choices.push_back(Choice::Base("Your only option is to try to get to speak to the Sultan while he is outside the palace", 414));

        Controls = Story::Controls::STANDARD;
    }
};

class Story307 : public Story::Base
{
public:
    Story307()
    {
        ID = 307;

        Text = "You steer a course between the pirates and their prey. The prow slices the waves, but the wind seems to favour the pirate ship. You see its triangular black sails looming towards your stern. A raven figurehead glares from its prow.\n\nYour sailors rush to the rail. The pirate ship is bearing down relentlessly with the wind filling its sails. When you give the order to turn hard about, your helmsman stares at you doubtfully. \"That'll leave us dead in the water!\" he says.\n\nYou nod. \"Do it.\"\n\nYour ship turns to face the oncoming pirates. You can see their faces now: eager rapacious grins, eyes barren of pity. The wind knocks your sails flat and your ship lurches to a standstill, rocking to and fro. Your own crew's groan of dismay is echoed by a vaunting cheer from the pirates. They think you are a sitting duck. You watch calmly as they sail closer... closer...\n\nShuddering violently, the pirate ship comes to a dead halt. Those cruel grins vanish when the pirates see how you've lured them onto a sandbank just below the surface. Now it is they who are helpless. Calling a rapid-fire volley of instructions to the marines, you bring your own vessel around within hailing distance and tell the pirates that you are ready to take their surrender. Stuck fast on the sandbank, they have no choice.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 372; }
};

class Story308 : public Story::Base
{
public:
    Story308()
    {
        ID = 308;

        Text = "Time becomes a blur. Leaving the sand dunes behind, you enter a region of barren grey rock. The howling of the wind is like a dirge, and the trembling waves of heat cause strange images to hover above the horizon.\n\n\"I have heard the voices of the celestial maidens calling me to Paradise,\" avers one man. The next morning he has wandered away from the camp and cannot be found.\n\nYou press on. Everyone fears that the desert will become their grave, but no one dares to say it. Then you see a band of six white-robed Bedouin riding towards you with raised spears. \"God has abandoned us!\" wails Hakim, falling to his knees. \"These devils will slay us and eat our flesh.\"\n\nThe Bedouin rein in at a spear-cast's distance and call out to you in arrogant tones: \"This is our desert. To pass on you must pay a toll of half your goods.\"\n\nYou glance around. Hakim is too terrified to take charge. The others look on with dull leaden looks. It is left to you to decide how to deal with this challenge.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to negotiate", 330));
        Choices.push_back(Choice::Base("Attack", 352));
        Choices.push_back(Choice::Base("Turn aside to avoid any trouble", 373));

        Controls = Story::Controls::STANDARD;
    }
};

class Story309 : public Story::Base
{
public:
    Story309()
    {
        ID = 309;

        Text = "The Lord of the Desert bids you rise. Not kindly -- his voice is laden with menace. When you see his naked sword glistening in the light, you know what is to come.\n\n\"Come, mortal!\" he cries. \"Your last moment is at hand. Will you stand with limbs shaking, or will you fight to save yourself? Fight boldly, and I may even be merciful.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Draw a SWORD now", 13, Choice::Type::ANY_ITEM, {Item::SWORD, Item::JEWELLED_SWORD}));
        Choices.push_back(Choice::Base("Fight him unarmed", 331));
        Choices.push_back(Choice::Base("Try to hide in the curtained alcove", 353));
        Choices.push_back(Choice::Base("Try to hide in one of the huge stone jars", 374));

        Controls = Story::Controls::STANDARD;
    }
};

class Story310 : public Story::Base
{
public:
    Story310()
    {
        ID = 310;

        Text = "You give a sudden whoop of delight that frightens the others. They think the ordeal has sent you mad. Hakim recoils in horror when you seize his sleeve and say, \"Sandstorm? That's no sandstorm. It's the answer to our prayers.\"\n\n\"There is no majesty nor power except in God,\" says Rahman, the portly scribe who keeps the accounts.\n\nYou round on him. You know you must present a wild sight, with your joyful grin and feverish stare. You see his look of shock and speak to calm him, saying, \"It is not for me to guide you. God guides those He chooses to.\"\n\nYou set off with a determined stride. The others murmur doubtfully, but soon see they have no hope if they do not trust you. Tugging the camels, they follow you towards the spot where you saw the dark cloud.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 354; }
};

class Story311 : public Story::Base
{
public:
    Story311()
    {
        ID = 311;

        Text = "You look at the sun, now dipping low in the west. How can you possibly build a tower in the space of one night?";

        Choices.clear();
        Choices.push_back(Choice::Base("[CUNNING] will do the trick", 333, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Use [MAGIC]", 355, Skill::Type::MAGIC));
        Choices.push_back(Choice::Base("Go off to explore the tower", 377));
        Choices.push_back(Choice::Base("Use the LAMP of Antar to slip away", 495, {Item::LAMP_OF_ANTAR}));
        Choices.push_back(Choice::Base("Urge the other sailors to help you fight the shark men", 108));
        Choices.push_back(Choice::Base("Wait until the dwarf wakes up and try to reason with him", 397));

        Controls = Story::Controls::STANDARD;
    }
};

class Story312 : public Story::Base
{
public:
    Story312()
    {
        ID = 312;

        Text = "You take cover in the bushes as the riders draw near. All four are clad in white robes, with doeskin boots and glinting silver filigree across their cloaks. All four carry spears, and all have swords and long curved knives at their belts. But they are not all alike in every way, for one wears a blankly serene mask fashioned from polished ivory.\n\nThe masked one speaks in a voice of honey, of music: \"I am the Sultan of Nishapur. The gazelle you took was mine, not yours.\"\n\n\"All gifts are given by God,\" says Abdullah defiantly. \"Besides, Nishapur is far from here and, since you wear a mask, who can say whether you speak the truth?\"\n\n\"I wear a mask,\" replies the other, \"because my gaze would shrivel you.\" His voice remains placid but with the merest lacing of menace, like a tart taste of poison mixed with sweet date wine.\n\nThe three knights brandish their spears. Events are about to turn nasty.";

        Choices.clear();
        Choices.push_back(Choice::Base("Emerge and stand with your comrades", 398));
        Choices.push_back(Choice::Base("Stay in hiding", 420));

        Controls = Story::Controls::STANDARD;
    }
};

class Story313 : public Story::Base
{
public:
    Story313()
    {
        ID = 313;

        Text = "Just as the Sultan removes his mask, you step forward and fling the CLOAK across his face. He claws at it, blinded for an instant. The three knights growl deep in their throats and go for their swords.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::SWORD}))
        {
            return 357;
        }
        else
        {
            return 335;
        }
    }
};

class Story314 : public Story::Base
{
public:
    Story314()
    {
        ID = 314;

        Text = "You remember the cat's weird knack of adding inches to its tail each time it hears a lie. \"Then that's how we'll escape,\" says Azenomei brightly when you tell him.\n\nYou shake your head. \"The tail soon shrinks again, and the grille's at least twenty feet up.\"\n\nHis eyes show a sly glint. \"I know a thousand lies, each more scandalous than the last. We'll wait till it's dark.\"\n\nAt midnight he wakes you and then, bending close to the cat's ear, he starts to whisper to it. Instantly the tail shoots up, growing longer and longer, until it reaches to the grille. \"Climb quick,\" says Azenomei, tossing you the keys.\n\nThe two of you ascend and unlock the grille. After more than a week in the noxious air of the cell, the night breeze tastes as sweet as oasis water. Azenomei takes back his bunch of keys. You notice the cat's tail is shrinking again, so you grab it and haul the animal up after you. Who knows, it might come in useful again.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 358; }
};

class Story315 : public Story::Base
{
public:
    std::string PreText = "";

    Story315()
    {
        ID = 315;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "Cold tongues of magical flame blast from his fingers. They lick around your limbs and you feel as though shards of ice are being hammered into your bones.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            DAMAGE = -3;

            PreText += "[AGILITY] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAREM}))
            {
                Choices.push_back(Choice::Base("Use [MAGIC]", 359, Skill::Type::MAGIC));
                Choices.push_back(Choice::Base("Use the Jericho HORN", 381, {Item::JERICHO_HORN}));
                Choices.push_back(Choice::Base("Fight", 410));
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 337; }
};

class Story316 : public Story::Base
{
public:
    Story316()
    {
        ID = 316;

        Text = "You tell the cat a couple of lies. Its tail grows a few inches but then, as before, shrinks back to its original length.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [STREETWISE]", 382, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("Use [FOLKLORE]", 382, Skill::Type::FOLKLORE));
        Choices.push_back(Choice::Base("Find something else to use", 204));

        Controls = Story::Controls::STANDARD;
    }
};

class Story317 : public Story::Base
{
public:
    Story317()
    {
        ID = 317;

        Text = "Jafar hurls the knife. The Caliph gives a groan and starts to crumple across his silk cushions like a flower wilting in the sun. Jafar hardly waits to celebrate his evil deed. Seeing the look in your eyes, he flees out of the room.\n\nYou gained the codeword IRIS.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::IRIS});
    }

    int Continue(Character::Base &player) { return 339; }
};

class Story318 : public Story::Base
{
public:
    Story318()
    {
        ID = 318;

        Text = "You place the HAWK on your shoulder, where it sits without protest.";

        Choices.clear();
        Choices.push_back(Choice::Base("Avail yourself of one of the magnificent JEWELLED SWORDs hanging on the wall", 450));
        Choices.push_back(Choice::Base("Leave without them", 93));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::HAWK});
    }
};

class Story319 : public Story::Base
{
public:
    Story319()
    {
        ID = 319;

        Text = "A narrow winding staircase leads up to the roof. You can hear the guards scrambling up behind you, and Jafar's voice echoes from the bottom of the stairwell.\n\nYou run over to the parapet and look around for an escape route. Nearby is the roof of the gatehouse, just a little lower than the level of the parapet. If you could make it to the gatehouse you could descend easily to the ground and make your getaway. The snag is that it is almost ten metres away. No one could make that jump.\n\nShouts from behind warn you that the guards have reached the top of the stairs. Just as you are resigning yourself to the thought of a futile death, you notice a flagpole sticking out from the wall just below the parapet. A gonfalon dangles from it, moving slowly in the gentle night breeze, casting its shadow across a moonlit balcony below. A gap of only six metres separates the tip of the flagpole from the gatehouse roof. A good athlete might make the jump.";

        Choices.clear();
        Choices.push_back(Choice::Base("[AGILITY] Try to jump to the gatehouse", 340, Skill::Type::AGILITY));
        Choices.push_back(Choice::Base("Rely on [CUNNING]", 406, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Try [MAGIC]", 428, Skill::Type::MAGIC));
        Choices.push_back(Choice::Base("You are cornered and must fight", 447));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::HAWK});
    }
};

class Story320 : public Story::Base
{
public:
    Story320()
    {
        ID = 320;

        Text = "The guards look up amazed as you whisk the curtains aside and step out onto the deck. In an instant they have drawn their swords and are bearing down on you with murder in their eyes.\n\nThe nearest swings his blade and you duck, hearing the sharp steel hiss over your head and strike the wooden post of the kiosk with a dull thunk. As your foe tugs desperately at the sword to free it, you stamp on his foot and follow through with a vicious blow to his stomach. The others crowd in behind him, keen to try their mettle against you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::JEWELLED_SWORD}))
        {
            return 208;
        }
        else
        {
            return 231;
        }
    }
};

class Story321 : public Story::Base
{
public:
    std::string PreText = "";

    Story321()
    {
        ID = 321;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "Your blows land solidly. The nearest warrior grunts and folds around the knee you have brought up hard into his stomach. Smashing your forearm into the side of his neck where the helmet gives no protection, you send him reeling aside. He collides with one of the others and both go sprawling.\n\nAs you whirl to face the third warrior, he brings up his sword and aims the tip at your heart. You fling yourself aside and the blade just nicks your arm. Stepping closer, you grab his forearm and drive the stiffened fingers of your other hand deep into his solar plexus. A gasp of pain issues from the iron visor as he crumples. But by now the other two have picked themselves up. You seem to be getting the better of them, but weight of numbers could still tell against you. Yussuf is no help -- he just cowers at the end of the gallery bleating like a lost lamb.\n\n";

        auto DAMAGE = -3;

        if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -1;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 386; }
};

class Story322 : public Story::Base
{
public:
    Story322()
    {
        ID = 322;

        Text = "Catching up with the man, you remonstrate with him for suggesting you bear a curse. \"This BLACK JEWEL I wear is a sure defence against evil sorcery,\" you point out.\n\n\"Whoever told you that was a prince of liars,\" he vows. \"You have been tricked, I fear. But I know a person who can rid you of the curse.\"\n\n\"At a price, I suppose?\"\n\n\"Of course. But what price is too high if paying it will save your soul?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Go with him", 489));
        Choices.push_back(Choice::Base("Go back to the ship", 301));

        Controls = Story::Controls::STANDARD;
    }
};

class Story323 : public Story::Base
{
public:
    Story323()
    {
        ID = 323;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 367;
        }
        else
        {
            return 388;
        }
    }
};

class Story324 : public Story::Base
{
public:
    Story324()
    {
        ID = 324;

        Text = "The jinni comes in answer to your summons. Surveying the chanting mage on the jetty, he turns to you and says, \"What is it you would have me do?\"\n\n\"Deflect the curse!\"\n\nThe jinni shrugs. \"His curse has no power. You are in the lap of fate now. I can save you from what is to come, but how do you know that matters will then turn out for the best?\"\n\n\"This is meaningless prattle. Steer our ship safely to a friendly port. I command you.\"\n\nStill he demurs. \"I say again, if I help you now then in the long run it may be worse for you. Will you bid me a third time? Then I must obey.\"\n\nWhat will you do?";

        Choices.clear();
        Choices.push_back(Choice::Base("Dismiss the jinni and trust to fate", 346));
        Choices.push_back(Choice::Base("Insist that he does as he is told", 368));

        Controls = Story::Controls::STANDARD;
    }
};

class Story325 : public Story::Base
{
public:
    Story325()
    {
        ID = 325;

        Image = "images/rokh.png";

        Text = "The legends were true. The rokh's nest is strewn with fragments of DIAMOND, some of them as big as a large shield. Any one of them would make your fortune -- which is just as well, because you could only carry one on the precarious descent.\n\nThere is something else in the nest: a JEWELLED METAL KEY as long as your forearm. You lick your lips uncertainly. Which is it to be: the JEWELLED KEY, or a fragment of DIAMOND? You can only choose one of these.";

        Bye = "Then you descend the same way you came up.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::JEWELLED_KEY, Item::DIAMOND};

        Limit = 1;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAREM}))
        {
            return 159;
        }
        else
        {
            return 480;
        }
    }
};

class Story326 : public Story::Base
{
public:
    std::string PreText = "";

    Story326()
    {
        ID = 326;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "You close in quickly to a distance where he cannot get a good angle for striking. One punch lays him flat out, but he manages to gash you across the thigh as he falls.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -1;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 434; }
};

class Story327 : public Story::Base
{
public:
    Story327()
    {
        ID = 327;

        Text = "At your command, the jinni blows a thick cloud of smoke out of the hearth. The ghouls are reduced to helpless coughing and are powerless to stop you from leaping back out of the doorway. There is the smack of a meaty fist and a yowl of pain as one of the ghouls, taking a blind swing in the smoke, hits his brother by mistake. As you hurry away down the hillside you can hear their roars of anger rattling the hilltops.\n\n\"Am I safe now?\" you whisper to your RING.\n\n\"Hide in a cave till sunrise,\" replies the jinni's voice. \"The she-ghoul will try to use her wiles to find you, but I'll confound her with spells of my own.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 260; }
};

class Story328 : public Story::Base
{
public:
    Story328()
    {
        ID = 328;

        Image = "images/filler2.png";

        Text = "Cairo market has few bargains to offer because of the problem of the pirates, but you find the following goods for sale: WATER BOTTLE, BOW, MIRROR, and SWORD.";

        Choices.clear();
        Choices.push_back(Choice::Base("Offer to help catch the pirates", 306));
        Choices.push_back(Choice::Base("Leave the city", 349));

        Controls = Story::Controls::SHOP;
    }

    void Event(Character::Base &player)
    {
        Shop = {{Item::WATER_BOTTLE, 5}, {Item::BOW, 40}, {Item::MIRROR, 30}, {Item::SWORD, 30}};
    }
};

class Story329 : public Story::Base
{
public:
    std::string PreText = "";

    Story329()
    {
        ID = 329;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "A salvo of arrows fly from your bow, carrying flaring red fire into the enemy's black sails. The pirates are thrown into immediate confusion. While they swarm across the deck like hornets, colliding with each other in their hurry to throw water on the burning canvas, you bring your own vessel in close for boarding.\n\nYou are first to leap across the rail, your marines taking courage from your example. The pirates muster a defiant roar as they raise their swords and rush to meet you, but they are men who prefer a helpless foe. Not used to fighting a defensive battle, they soon begin to weaken in the teeth of your onslaught.\n\nEven though victory is certain, there is a chance you might be killed in the fighting.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = 0;

            PreText += "[SWORDPLAY] You are uninjuired.";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -1;

            PreText += "[WRESTLING] ";
        }

        if (DAMAGE < 0)
        {
            Character::GAIN_LIFE(player, DAMAGE);

            PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 372; }
};

class Story330 : public Story::Base
{
public:
    Story330()
    {
        ID = 330;

        Text = "The Bedouin refuse to see reason and are now so indignant that they also demand your water.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave", 373));
        Choices.push_back(Choice::Base("Fight", 352));

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::CUNNING, Skill::Type::WILDERNESS_LORE}))
        {
            return 394;
        }
        else
        {
            return -1;
        }
    }
};

class Story331 : public Story::Base
{
public:
    Story331()
    {
        ID = 331;

        Text = "How will you attack?";

        Choices.clear();
        Choices.push_back(Choice::Base("Try a punch", 468));
        Choices.push_back(Choice::Base("Try a leg sweep", 242));
        Choices.push_back(Choice::Base("Wait for him to attack and then dodge aside", 219));

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::WRESTLING, Skill::Type::AGILITY}))
        {
            return 173;
        }
        else
        {
            return -1;
        }
    }
};

class Story332 : public Story::Base
{
public:
    std::string PreText = "";

    Story332()
    {
        ID = 332;

        Choices.clear();
        Choices.push_back(Choice::Base("Stand you ground", 237));
        Choices.push_back(Choice::Base("Back away", 46));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The demon swoops to renew its attack. Claws like razors rake across your flesh, but you ignore the pain and lash out with blows of your own. Each time you hit, you feel the crack of chitin and the demon utters a sibilant scream.\n\n";

        auto DAMAGE = -3;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -2;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nAfter a short exchange of blows, the demon breaks off and rises again into the air to heal its wounds. If only you had the same advantage.";
        }

        Text = PreText.c_str();
    }
};

class Story333 : public Story::Base
{
public:
    Story333()
    {
        ID = 333;

        Text = "The captain pulls off his turban and weeps into it. \"Even working all together, it would take us weeks to build that tower's twin!\" he wails. \"Alas, we can only wait and see what fate the dwarf has in store.\"\n\n\"Why wait?\" You take hold of the cushion by one corner and turn it around so that the dwarf's head is pointing away from the sun. Ignoring the horrified looks of your comrades, you give a bold laugh and shake him awake.\n\nHe opens one eye, then the other. He yawns. \"Morning already?\"\n\nYou gesture towards the tower. \"Yes. And see, we've built your tower.\"\n\nHe sits up, blinks and rubs his eyes. Uttering an angry oath, he leaps to his stumpy legs and glares at you. \"But what has happened to my own tower? It lies in ruins!\"\n\n\"There weren't quite enough stones, I'm afraid. We had to pull a few extra out of your tower's foundations and -- well, it toppled, as you can see.\"\n\nThe dwarf looks at the seven shark men, but they are apparently too dull-witted to make any comment. Contentment shows in a tight little smile as he replaces his crown. \"Oh well,\" you hear him mutter to himself, \"at least I won't have to worry about the egg any more.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 441; }
};

class Story334 : public Story::Base
{
public:
    Story334()
    {
        ID = 334;

        Image = "images/filler5.png";

        Text = "At a gesture, the rope uncoils itself like a snake and rises until it stretches to the top of the tower. The sailors fall back with superstitious moans, but you are undaunted. Seizing the rope, you climb swiftly up to the balcony.\n\nThe chamber under the dome is bare of any decoration or feature except for a podium in the middle, where a large grey egg rests on a velvet cushion.\n\nYou step forward. The whole tower must have been built for the single purpose of keeping this egg safe.";

        Choices.clear();
        Choices.push_back(Choice::Base("Touch the egg", 290));
        Choices.push_back(Choice::Base("Climb back down to the ground", 267));

        Controls = Story::Controls::STANDARD;
    }
};

class Story335 : public Story::Base
{
public:
    Story335()
    {
        ID = 335;

        Text = "You find yourself staring into the Sultan's face. His right eye is normal, but his left eye shines like a droplet of black venom. You feel a chill taking the strength from your limbs. You try to raise your arm, but it is lifeless. With a moan, you slump to the ground and darkness drops across you. It is the end.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story336 : public Story::Base
{
public:
    Story336()
    {
        ID = 336;

        Image = "images/filler3.png";

        Text = "In the still silence of midnight, with everyone else asleep, you crouch beside Azenomei and make your plans for escaping from this dark hole.\n\n\"One of my keys will certainly fit the lock,\" he whispers. \"Give me your MAGIC SLIPPERS so that I can get up there. Once I'm out, I'll drop them back down.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Trust him", 380));
        Choices.push_back(Choice::Base("Insist on being the one to go first", 401));

        Controls = Story::Controls::STANDARD;
    }
};

class Story337 : public Story::Base
{
public:
    Story337()
    {
        ID = 337;

        Text = "Ayisha sings a spell which sends a hail of hard pebbles flying from nowhere into Azenomei's face. He falls back, dazed, with blood streaming from a dozen wounds.\n\n\"Quickly!\" shrieks Ayisha. \"Get him while he's still stunned.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack him", 423));
        Choices.push_back(Choice::Base("Run for it while you have the chance", 445));

        Controls = Story::Controls::STANDARD;
    }
};

class Story338 : public Story::Base
{
public:
    Story338()
    {
        ID = 338;

        Image = "images/filler2.png";

        Text = "The slippers make you weightless and you drift high up into the sky until finally, penetrating the clouds, you see the nest of the rokh. Success is within your grasp.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 325; }
};

class Story339 : public Story::Base
{
public:
    Story339()
    {
        ID = 339;

        Text = "Despite the commotion behind you, there is no time to wait for the palace guards to arrive on the scene. You are determined not to let Jafar get away. You chase him down a wide staircase and on through an empty hall that echoes to the sound of his ragged breath as he struggles along in his heavy robes. Crossing a small courtyard, he glances back to see you gaining on him. You pursue him the length of a covered passage, emerging onto a parade ground which abuts the royal stables. And here you skid to a halt, for Jafar has turned to wait for you.\n\nHe takes a jar from his robes and raises it, saying a few words in the tongue of the idolaters who held sway in this land before the coming of the Prophet. Then he casts the jar down. It shatters on the cobblestones at his feet.\n\nA swirl of smoke rises, thickening into solid form. The creature Jafar has conjured has long limbs ending in extravagant talons. Its body gleams like old earthenware in the moonlight. Its eyes are brighter than the stars. Strangest of all are its wings -- translucent panes with a filigree of silver, like some huge insect's.\n\nJafar says, \"I'll leave you now to enjoy my demon's embrace.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 490;
        }
        else
        {
            return 216;
        }
    }
};

class Story340 : public Story::Base
{
public:
    Story340()
    {
        ID = 340;

        Text = "Hoisting yourself over the parapet, you dangle down until your feet find purchase on the flagpole. You hold your arms out for balance and skip nimbly like a tightrope walker to the end of the pole.\n\nBy this time the guards have reached the edge of the roof. \"Don't be a fool!\" one of them shouts. \"You can't make that jump.\"\n\nHe may be right, but you do not hesitate. You are dead anyway if they catch you. You fling yourself into empty space. Time seems to slow down as you see the gatehouse roof come looming towards you. Then your fingers catch on the cornice and you swing yourself up onto the battlements.\n\nThe guards are shouting wildly, trying to attract the attention of the sentries on watch in the gatehouse. As you descend, a portly soldier emerges from a doorway and starts to relieve himself against the wall. He glances as you sweep past, but by the time he realizes you're an intruder you have reached the street and made your getaway.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 383; }
};

class Story341 : public Story::Base
{
public:
    std::string PreText = "";

    Story341()
    {
        ID = 341;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Just as you reach the bottom of the stairs, the door across the hall crashes open and a dozen more guards rush in, obviously alerted by the noise. Jafar clutches the rail of the balustrade above and shakes with wrath as he screams, \"I'll behead any man who lets the villain escape!\"\n\nRaising their swords, the guards charge across the hall. You push over a tall candelabrum behind you to delay them while you dart back along a passage leading deeper into the palace. Curses resound along the passage as the guards disentangle themselves from the fallen candelabrum. You hear the tramp of running feet. They are right behind you.\n\nTurning a corner, you stop short with a groan. The passage ends in an alcove containing a tall alabaster jar. You have reached a dead end.";

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::STREETWISE, Skill::Type::LUCK}))
        {
            PreText += "\n\nYou can only whirl to face your pursuers.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::STREETWISE, Skill::Type::LUCK}))
        {
            return 465;
        }
        else
        {
            return 447;
        }
    }
};

class Story342 : public Story::Base
{
public:
    Story342()
    {
        ID = 342;

        Text = "\"No doubt the guards check on you from time to time?\"\n\nShe nods. \"One of them comes to look in through the curtain every hour or so. If you are thinking we might slip away, I advise you to forget it. As soon as they noticed I was gone they'd be sure to search every ship on this stretch of the river.\"\n\n\"Then we must make sure they don't notice it. Not until tomorrow, at least.\"\n\nGathering the cushions lining the floor of the kiosk, you start to arrange them carefully. The woman watches with furrowed brow for a moment, then sees what you are planning. Removing her shawl, she drapes it over the pile of cushions and adds a few trinkets of jewellery to complete the effect.\n\nThe two of you stand back and appraise your handiwork. Anyone looking in through the curtains would certainly think there was a figure lying there curled up asleep.\n\nYou lower her silently over the side and you both swim back to your own vessel.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 254; }
};

class Story343 : public Story::Base
{
public:
    std::string PreText = "";

    Story343()
    {
        ID = 343;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "You fling the CLOAK over the nearest warrior's head. While he is struggling blindly to get free, you kick his legs out from under him and stoop to whack his head against the ground. The iron helmet rings like an anvil under a hammer. The effect on the warrior must be rather the same as putting his head inside a bell. He squirms away, clutching his ears and writhing in pain.\n\nThe other two rush in to attack. As they step onto the CLOAK, you whisk it out from under them and they go sprawling. Glancing at Yussuf, you see that he will be of no use in this fight. He is cowering wide-eyed at the end of the gallery with his fist stuffed into his mouth. Still, you seem to be getting the better of the three warriors with just your bare hands.\n\nThe battle is brief.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            Character::GAIN_LIFE(player, -2);

            PreText += "\n\nYou LOSE 2 Life Point(s).";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 386; }
};

class Story344 : public Story::Base
{
public:
    Story344()
    {
        ID = 344;

        Text = "Two men stand back in the shadows of the bath-house doorway. You notice at once they are villains. One has had his ears cropped for some crime or other, the other lacks a nose. The stout sticks they hold behind their backs are a dead giveaway too.\n\nThe man leading you down the alley sees you hesitate and asks what the matter is.\n\n\"Do you think me so witless that I can be lured into a den of thieves?\" you say. \"Be thankful I don't summon the city militia and have you flogged.\"\n\nHearing this, his two cronies emerge from the bath-house and advance menacingly towards you. You beat a swift retreat to the main street. Glancing back over your shoulder, you see them watching you go with disappointed scowls.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 301; }
};

class Story345 : public Story::Base
{
public:
    Story345()
    {
        ID = 345;

        Text = "She suddenly stops her sobbing and gives you a scowl of such blood-freezing hatred that you hope never to see the like again. As you step back in dismay, she leaps up and runs off between the clumps of cloud. You follow for a short distance, but you cannot find any trace of her. Seeing the spires and domes of the city not far off, you make your way towards it.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 302; }
};

class Story346 : public Story::Base
{
public:
    Story346()
    {
        ID = 346;

        Text = "You sail downriver to the sea. As you go, clouds thicken like soot in the sky and the sails flutter fretfully as the first stirrings of a high wind come howling down. Lightning spits across the sky, rattling great blows against the gong of the heavens. The waters surge around your prow, sending high spurts of foam across the deck.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 131; }
};

class Story347 : public Story::Base
{
public:
    std::string PreText = "";

    Story347()
    {
        ID = 347;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "His muscular bulk is no protection against a deft sword-thrust to the heart. But in your hurry to dispose of him, you step straight into a solid punch to the jaw. You reel back, blood spurting from your nose, as the guard sinks to the ground.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }
};

class Story348 : public Story::Base
{
public:
    Story348()
    {
        ID = 348;

        Text = "\"Bit puny for ghouls, aren't you?\" you say to the brothers as they start to tie you up.\n\nThe mother overhears this. \"Don't you listen to that nonsense,\" she snaps. \"Those mortals are sly little wretches.\"\n\n\"What do you mean, puny?\" says one of the brothers, ignoring her.\n\nYou shrug casually. \"I've seen lots of ghouls tougher than you. Dozens.\"\n\nThe other one glares at you. \"What's your game, eh? I'll have you know we're as strong as they come. A good diet of mortal flesh sees to that, eh, Ma?\"\n\n\"That's right, son,\" cackles the crone as she stirs the pot.\n\n\"Believe whatever you like, if it makes you feel better,\" you say. \"I'm going to die soon, so it doesn't matter to me. I'm just saying you're a pathetic pair of undernourished ghouls.\"\n\nThey fling the ropes aside. \"Prove it!\"\n\n\"All right. How about a race around the hill? If you two beat me, you'll have worked up a good appetite. If I win, you let me go.\"\n\n\"You'll never win!\" they snort. Taking no notice of their mother's outraged glare, they take you outside. \"Back in a minute, Ma!\" one of them calls over his shoulder.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::CONCH}) && Character::VERIFY_ANY_SKILLS(player, {Skill::Type::FOLKLORE, Skill::Type::CUNNING, Skill::Type::AGILITY, Skill::Type::ARCHERY}))
        {
            Choices.push_back(Choice::Base("Use [FOLKLORE]", 56, Skill::Type::FOLKLORE));
            Choices.push_back(Choice::Base("Use [CUNNING]", 469, Skill::Type::CUNNING));
            Choices.push_back(Choice::Base("Use [AGILITY]", 102, Skill::Type::AGILITY));
            Choices.push_back(Choice::Base("Use [ARCHERY]", 124, Skill::Type::ARCHERY));
        }
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::CONCH}))
        {
            return 10;
        }
        else
        {
            return 147;
        }
    }
};

class Story349 : public Story::Base
{
public:
    std::string PreText = "";

    Story349()
    {
        ID = 349;

        Choices.clear();
        Choices.push_back(Choice::Base("Stop off at the oasis", 473));
        Choices.push_back(Choice::Base("Continue past the oasis", 15));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Leaving Cairo on foot, you head along the banks of the Nile. Soon you have left the fertile farmland behind, and you head on into wild territory where the Sultan's rule of law does not extend. Crocodiles splash the dun-coloured water, sliding down off the sun-drenched banks as you pass. You see boats plying their trade, but they stay in midstream. A lone traveller in these parts might easily be a brigand or a mad wizard, and the few peasants you see are fearful of approaching you.\n\nBeyond the river-bank lies a waterless wasteland. Soon the soles of your feet are hardened like leather and your tongue sticks to the roof of your mouth. In all directions the horizon is lost in a hot flat haze.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE) && !Character::VERIFY_ITEMS(player, {Item::Type::WATER_BOTTLE}))
        {
            Character::GAIN_LIFE(player, -1);

            PreText += "\n\nYou LOSE 1 Life Point.";
        }
        else
        {
            if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
            {
                Character::EMPTY(player, Item::Type::WATER_BOTTLE);

                PreText += "\n\nThe WATER BOTTLE is now EMPTY.";
            }
        }

        if (player.Life > 0)
        {
            PreText += "\n\nAfter days without seeing another soul, you reach an oasis. High palm trees sway against the sky. They are a rich dark green that almost looks black against the dazzling dust-draped landscape.";
        }

        Text = PreText.c_str();
    }
};

class Story350 : public Story::Base
{
public:
    int COUNT_APPLES = 0;

    Story350()
    {
        ID = 350;

        Image = "images/marketplace.png";

        Text = "The pirates have stifled trade, and the marketplace is denuded of goods. What there is fetches a high price. You stroll along beside the mats of the traders. A fat man seated on plump cushions beneath a stretched silk awning points to his dishes. \"Here is food of the far Orient,\" he says.\n\nYou look at the dishes piled with golden apples. \"A journey of weeks or months, yet these apples seem quite fresh.\"\n\n\"They are rich with enchantment,\" he replies. \"Each has the power to banish sickness and make injuries fade like...\"\n\n\"Like the dew of the gardens of Baghdad at dawn?\" You smile.\n\n\"Like footprints on a beach as the tide rolls over them.\"\n\n\"A veritable marvel. And how much do you want for these doubtless delicious fruits?\"\n\nHe flutters his fingers in calculation. \"Accounting you to be a pious traveller of good heart, with a discount for your poetic turn of phrase and the proper deduction for brisk business... Let us say, five dinars apiece.\"\n\nFive dinars would pay for a whole banquet.";

        Choices.clear();

        Controls = Story::Controls::SHOP;
    }

    void Event(Character::Base &player)
    {
        COUNT_APPLES = Item::COUNT_TYPES(player.Items, Item::Type::GOLDEN_APPLE);

        Shop = {{Item::GOLDEN_APPLE, 5}};
    }

    int Continue(Character::Base &player)
    {
        if ((Item::COUNT_TYPES(player.Items, Item::Type::GOLDEN_APPLE) - COUNT_APPLES) > 0)
        {
            return 467;
        }
        else
        {
            return 78;
        }
    }
};

class Story351 : public Story::Base
{
public:
    std::string PreText = "";

    Story351()
    {
        ID = 351;

        Bye = "You survive to see victory.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The pirates bear down towards your ship. As they get close, the shadow of their black sails falls across the deck, drawing a groan of fear from your marines.\n\nThe enemy's prow crashes hard into your rail, splintering the planks. Your men go pale with fear, but you are not daunted. Smashing your foot into the broken timber, you cry out: \"This ship's scuppered. Will you wait aboard her till she sinks? Those of you who want to live, follow me!\"\n\nYou leap across the rail towards the startled pirates. Your marines take courage from your example. The pirates fight furiously, but they are not used to fighting a defensive battle, and soon begin to weaken in the teeth of your onslaught.\n\n";

        auto DAMAGE = -7;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -4;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 372; }
};

class Story352 : public Story::Base
{
public:
    Story352()
    {
        ID = 352;

        Text = "The Bedouin respond to your defiance by digging their heels into their camels' flanks and riding forward with a shrill battle cry.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ARCHERY))
        {
            return 241;
        }
        else
        {
            return 264;
        }
    }
};

class Story353 : public Story::Base
{
public:
    Story353()
    {
        ID = 353;

        Text = "You dive through the curtain and find yourself in a cramped alcove. If you were hoping for an escape route, you're out of luck. You hear the Lord of the Desert stamping around his treasure hall. His sword makes angry swishing sounds, but for some reason he does not try to pursue you or drag you out of the alcove.\n\n\"How long can you hide in there?\" he snarls. \"Come out and face me, coward!\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::ROGUERY, Skill::Type::CUNNING, Skill::Type::MAGIC}) && !Character::VERIFY_ITEMS_ANY(player, {Item::SWORD, Item::JEWELLED_SWORD}))
        {
            Choices.push_back(Choice::Base("Fight him with your bare hands", 331));
        }
        else
        {
            Choices.push_back(Choice::Base("Use [ROGUERY]", 439, Skill::Type::ROGUERY));
            Choices.push_back(Choice::Base("Use [CUNNING]", 395, Skill::Type::CUNNING));
            Choices.push_back(Choice::Base("Use [MAGIC]", 417, Skill::Type::MAGIC));
            Choices.push_back(Choice::Base("Fight him with a SWORD", 13, {Item::SWORD, Item::JEWELLED_SWORD}));
        }
    }
};

class Story354 : public Story::Base
{
public:
    Story354()
    {
        ID = 354;

        Image = "images/filler4.png";

        Text = "You discover that the 'cloud' you saw was actually a swarm of locusts. They cover the ground, and you show the others how to catch them by throwing rugs, saddlebags and robes over them where they lie. As an added bonus, the locusts had discovered a patch of scrub which, when you dig down to the roots, reveals a trickle of water.\n\nThe others are squeamish about eating locusts. \"Are they not unclean creatures?\" says the scribe Rahman, looking dubiously at the plate of roasted insects you hand to him. But you notice that, all the same, he tucks in as hungrily as everyone else.\n\nYou journey on the next day with lightened spirits. \"Soon we'll reach the coast,\" says Hakim. \"Then we'll take the road north-west to Cairo. No more starvation or thirst to worry about. We're past the worst of it, my friends.\"\n\n\"We should stop at Mecca to make our thanks to God, master,\" suggests one of the camel-drivers.\n\nHakim looks reluctant. \"Ah, well, perhaps we'll do that on the way back. I'll lose money if these goods are late in getting to Cairo market.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("You also think that the caravan should stop off at Mecca", 101));
        Choices.push_back(Choice::Base("You are not worried about it", 123));

        Controls = Story::Controls::STANDARD;
    }
};

class Story355 : public Story::Base
{
public:
    Story355()
    {
        ID = 355;

        Text = "The jinni balks at the task you want to set him. \"To build an entire tower overnight!\" he cries, raising his bristly eyebrows. \"You think too much of my ability.\"\n\n\"I'm relying on you,\" you reply. \"We all are. This dwarf told us to build a tower. If he wakes to find we've failed, I fear an unpleasant conclusion to the matter.\"\n\nThe jinni considers for a moment, nods. \"I'll grant this last wish,\" he proposes, \"and then you must give me my freedom.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Agree with the jinni and make your last wish", 198));
        Choices.push_back(Choice::Base("Dismiss the jinni and try another tack: [CUNNING]", 333, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Explore the tower", 377));
        Choices.push_back(Choice::Base("Sneak off using the LAMP of Antar", 495, {Item::LAMP_OF_ANTAR}));
        Choices.push_back(Choice::Base("Attack the shark men", 108));
        Choices.push_back(Choice::Base("Wait and see what the dwarf does when he wakes up", 397));

        Controls = Story::Controls::STANDARD;
    }
};

class Story356 : public Story::Base
{
public:
    Story356()
    {
        ID = 356;

        Image = "images/filler2.png";

        Text = "A hurried inspection of the ship reveals that everyone aboard died mysteriously and quite suddenly. \"At first I feared it was plague,\" says the captain, \"but there is nothing in the log to suggest trouble. It seems they just went to sleep one night and never woke up.\"\n\nThe cargo hold is found to be full of porcelain and glassware, which should fetch a tidy sum in the east. The captain, deciding that it is too late today to sort through the cargo, orders the two ships tethered. \"Tomorrow we will give her a thorough inspection,\" he says. He points to you. \"You will keep watch on board her tonight.\"\n\nIt is plain from the looks of the other sailors that they would not relish spending the night on a ship full of dead men. You are not all that keen yourself, but orders are orders. Taking a lantern, you go across to the other ship.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            return 107;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            return 130;
        }
        else
        {
            return 153;
        }
    }
};

class Story357 : public Story::Base
{
public:
    std::string PreText = "";

    Story357()
    {
        ID = 357;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You drive the sword right through the Sultan so that the tip pushes out of his back. His entrails spill out onto the moss. The three knights stand looking on in shock, then lift the body across their late master's horse and lead it away. You think they have forgotten you, but at the edge of the clearing one turns and casts his spear. It strikes your shoulder.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou staunch the bleeding while they ride off between the trees. There is nothing you can do for your friends, but at least you were able to avenge them. As you go to leave, you notice a BLACK JEWEL lying on the moss by your feet.";
        }

        Text = PreText.c_str();

        Take = {Item::BLACK_JEWEL};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story358 : public Story::Base
{
public:
    Story358()
    {
        ID = 358;

        Image = "images/filler4.png";

        Text = "The two of you manage to slip out of the city the next morning on the back of an ox-cart. The owner is startled when the sacks of grain on the back of his cart are suddenly thrown aside to reveal two scruffy young vagabonds.\n\nAzenomei gazes back at the city and gives a hearty laugh. \"A pox on that place. I'll never go there again, I can tell you.\" He turns to you. \"And where are you bound now, my friend?\"\n\n\"I left Baghdad in search of fame and fortune. But I was accused of being an infamous thief, and now I have no money.\"\n\n\"You could do worse than throw in your lot with me,\" declares Azenomei. \"I'm heading across the desert to rescue my sister. She was spirited away by a jinni who imprisoned her in a bronze citadel. I can promise you as much adventure as you can take.\"\n\nIf someone had said that to you just a few months ago, you would have assumed they were mad. Now you have seen many marvels with your own eyes. But you have not learned to be careless of risk.\n\n\"A jinni's citadel, you say? That may be a little more adventure than I can take.\"\n\nAzenomei waits for your decision.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go with him across the desert", 270));
        Choices.push_back(Choice::Base("Go your own way", 223, Choice::Type::GET_CODEWORD, {Codeword::Type::NOOSE}));

        Controls = Story::Controls::STANDARD;
    }
};

class Story359 : public Story::Base
{
public:
    Story359()
    {
        ID = 359;

        Text = "A swirl of vapour emerges from the RING, clotting in midair into the shape of your jinni. He looks across the chamber with a groan of dread.\n\n\"Azenomei al-Umara!\" Turning to you, he mutters, \"This is one of the lords of the jinn. He is far mightier than I. If you send me forth to battle him, it may mean my death.\"\n\n\"Your life's purpose is to serve me,\" you retort. \"Attack!\"\n\nTaking the form of a shaggy black lion, he leaps on Azenomei. The tumult of roars, shrieks and bone-crunching blows is enough to freeze your blood. It is soon clear that your jinni was right -- he's no match for Azenomei.";

        Choices.clear();
        Choices.push_back(Choice::Base("Recall the jinni and attack Azenomei yourself", 112));
        Choices.push_back(Choice::Base("Watch to see how the fight goes", 43));

        Controls = Story::Controls::STANDARD;
    }
};

class Story360 : public Story::Base
{
public:
    Story360()
    {
        ID = 360;

        Text = "You give the command for the rope to rise, taking a firm hold of the top so that you are borne upwards, through the wispy clouds, to the thin clean air where the rokh has its eyrie.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 325; }
};

class Story361 : public Story::Base
{
public:
    std::string PreText = "";

    Story361()
    {
        ID = 361;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Ishak of Mosul is one of the Caliph's favourite musicians. You know that he lives the life of a recluse in a house on the outskirts of the city. Calling on him, you are invited to dine. For almost an hour Ishak talks to you of various matters, but he is scrupulous about the laws of courtesy and does not demand to know why you have come.\n\nAt last you explain. \"I must see the Caliph. It is very important.\" Ishak looks out of the window. \"It is after dark. The curfew is in force.\"\n\nYou go to stand beside him, looking deep into his eyes. \"It's very important, Ishak.\"\n\nHe paces to and fro, then comes to a decision. Telling you to wait, he slips out into the night. Quite a short time later, the door bursts open and a group of soldiers dash in. Ishak stands in the doorway behind them, wringing his hands.\n\n\"It's not my fault,\" he says. \"They arrested me and made me lead them back here.\"";

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            PreText += "\n\nYou are seized and hauled away.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 446;
        }
        else
        {
            return 405;
        }
    }
};

class Story362 : public Story::Base
{
public:
    Story362()
    {
        ID = 362;

        Text = "\"The other reason? It is here,\" says Jafar, pulling a scroll from his sleeve. \"This CHART was brought to me by my loyal henchman, who got it from an African trader. It shows where I can find the nest of the great rokh, the bird with wings longer than a city's streets. It lays eggs of DIAMOND, and with just a few fragments of such an egg I could bribe the army and make myself Caliph.\"\n\nThe slave's eyes are wide with wonder. \"When will you set out to seek this treasure, lord?\" she asks.\n\nJafar snorts. \"Me, risk my life climbing to the rokh's nest? I have no intention of doing so. I employ others for those tasks. Even now, my agents are combing the sordid dives and dens of a dozen cities searching for the famous thief Shazir.\"\n\n\"Shazir!\" The slave gasps. \"I have heard of that one's daring exploits. It was Shazir who stole the ruby known as Iblis's Eye from the treasury of the Sultan of Nishapur.\"\n\nJafar nods impatiently. \"Yes, and it will be the same Shazir who steals a piece of the rokh's egg for me. Now, come and help me change. This Robe of Honour is elegant, but it is also rather uncomfortable.\" He puts the chart down on a table and goes through a curtained archway into an inner room. The slave glides dutifully after him.\n\nYou look at the CHART and lick your lips. Just a few quick strides and you would hold the key to great treasure in your hands. But if you are discovered here, you will be beheaded as a common thief.";

        Choices.clear();
        Choices.push_back(Choice::Base("Creep over for a closer look at the CHART", 184));
        Choices.push_back(Choice::Base("Leave the palace now", 383));

        Controls = Story::Controls::STANDARD;
    }
};

class Story363 : public Story::Base
{
public:
    Story363()
    {
        ID = 363;

        Text = "You jump through into an empty chamber, slamming the door shut. You manage to wedge a candelabrum against it, but the guards are battering on the other side with the pommels of their swords. \"Break it down!\" you hear Jafar snarl.\n\nYour makeshift barricade won't hold them off for long. You look around, heart thudding like that of a cornered animal. The only route out of here is over a vine-covered balcony -- a drop of six metres or more to the hard flagstones below.\n\nThere is the sound of splintering wood. The guards are almost through the door. You have no time left to ponder. You must act now.";

        Choices.clear();
        Choices.push_back(Choice::Base("[MAGIC] Call on your jinni", 49, Skill::Type::MAGIC));
        Choices.push_back(Choice::Base("Jump from the balcony", 72));
        Choices.push_back(Choice::Base("Start climbing down using the vines for support", 95));

        Controls = Story::Controls::STANDARD;
    }
};

class Story364 : public Story::Base
{
public:
    Story364()
    {
        ID = 364;

        Text = "The woman goes ashen as she sees the jinni swirl up in a cloud of indigo vapour from your ring. Sheer amazement is the only thing that keeps her from crying out.\n\nThe jinni listens, fingering his tusks, as you explain the predicament. \"Let me rend them into small chunks and scatter them to the fishes, supreme one,\" he says eagerly as he peers out from the drapes at the six guards.\n\n\"Oh no,\" gasps the woman, finding her voice at last. \"It is not their fault. They're just doing as Jafar ordered.\"\n\nThe jinni looks to you. After a glance at the woman, you give him a nod. \"Do it without bloodshed,\" you say.\n\nShrugging, he turns himself into a gnat and flies out to where the guards are playing dice. Without them noticing, he alters the dice roll and then buzzes into one man's ear. The man looks up and glares at the man next to him. \"What do you mean, I cheated?\" he snarls.\n\n\"Cheated?\" replies the other. \"I never said any such thing.\"\n\n\"It must have been your guilty conscience speaking to you, Abdul, you lowborn dog,\" chortles another of the guards.\n\n\"Worthless excrement of a diseased camel!\" screams Abdul, leaping up and swinging a punch. Within seconds the brawl is whipped into a frenzy by the jinni's trickery. Soon six unconscious forms line the deck.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 254; }
};

class Story365 : public Story::Base
{
public:
    Story365()
    {
        ID = 365;

        Text = "You join Yussuf in a desperate scramble up the tunnel leading to the surface. But a twist in the passage just brings you to a dead end. Yussuf throws himself against the rock slab and claws at it, crying,\n\n\"This wasn't here a moment ago!\"\n\nThere is a deathly soft footstep right behind you. Before you can whirl to face your pursuers, something hits you in the middle of the back. Suddenly you feel dizzy. The light seems to be draining away into an inky haze.\n\nYussuf is screaming as he stares at your chest. You look down, and as your eyes flutter closed you see a slender sword point protruding between your ribs. It is slick with your own blood. This is the end.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story366 : public Story::Base
{
public:
    Story366()
    {
        ID = 366;

        Text = "There is no mistaking the telltale tug on your purse strings. You look down in time to see a scrawny urchin slice through the purse, snatch up your gold and run pell-mell away down the alley. You are about to give chase when you see two burly ruffians lurking in the entrance to the bath-house. Their scarred, hard faces leave you in no doubt that they would not hesitate to use those gnarled clubs they're holding.\n\nRealising that the man who led you here must be in league with the thieves, you look around. But he is already running off. Disgruntled at having been robbed, you slouch back towards the docks.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, -player.Money);
    }

    int Continue(Character::Base &player) { return 301; }
};

class Story367 : public Story::Base
{
public:
    Story367()
    {
        ID = 367;

        Image = "images/filler2.png";

        Text = "An old story you heard from your mother springs to mind. It concerned a sailor who was cast up to the heavens on a waterspout. His comrades all fell back to their doom, but he was clutching a MAGIC FLOWER which enabled him to walk on the clouds. Finding a city of scintillant gold, he dwelt among the people there and even married one of them. Many years later, he was able to leave when the cloud became lodged on top of a high mountain. He brought his wife down the mountainside with him, but she could not survive in the over-rich air and soon died.\n\nBearing this tale in mind, you decide it might be safer not to let go of the FLOWER.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::JASMINE_FLOWER});
    }

    int Continue(Character::Base &player) { return 345; }
};

class Story368 : public Story::Base
{
public:
    Story368()
    {
        ID = 368;

        Text = "You sail downriver to the sea. As you go, clouds thicken like soot in the sky and the sails flutter fretfully as the first stirrings of a high wind come howling down. Lightning spits across the sky, rattling great blows against the gong of the heavens. The waters surge around your prow, sending spurts of foam across the deck.\n\nThe sailors moan and start to pray for deliverance. You turn to the jinni, who exerts his magic to quell the storm. It rolls off into the east -- a yellow glimmering beyond the clouds, like the fires of Iblis the Destroyer.\n\nThe seas are left with a high swell, but soon that too dies down. With a satisfied smirk, the jinni becomes a coil of vapour that is sucked back into your RING.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 389; }
};

class Story369 : public Story::Base
{
public:
    Story369()
    {
        ID = 369;

        Text = "You put on a sudden burst of speed that takes the two guards completely by surprise. Dodging both lunges, you whirl in time to see their expressions of slack-faced disbelief as they spring together, each piercing the other on his blade. As they slump lifeless to the ground, you step up to the door and free the captain.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 412; }
};

class Story370 : public Story::Base
{
public:
    Story370()
    {
        ID = 370;

        Image = "images/filler1.png";

        Text = "The two sons are stocky and strong, but you can capitalize on their slow wits and clumsiness. The mother will be harder to beat, because legend has it that a she-ghoul can only be hurt by a weapon made of wood. Furthermore, you must strike well with your first attack. There are countless stories of ghoul-witches who have been felled by one blow, only to be replenished when a second blow was struck.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 305; }
};

class Story371 : public Story::Base
{
public:
    Story371()
    {
        ID = 371;

        Text = "Falling in with a group of marines who have just returned from a patrol of the Red Sea, you impress them with your knowledge of naval tactics. These men are slaves of the Sultan, well trained and fiercely loyal. Their officer vows to follow some of your suggestions on his next patrol. A few days later you see him with his commander as they emerge from the public bath-house, and the officer calls you over to introduce you.\n\nThe commander is a man with little practical experience, but he listens keenly to your tales of distant lands. When you tell him about the explosive powders of China and the incendiary liquid used by the Byzantine navy, he claps his hands in amazement. \"You must tell these stories to the Sultan himself. He is fascinated by such things.\"\n\n\"I would be delighted to do so. Also, I would like to explain to him about the ideas you and I have come up with for catching the Red Sea pirates.\"\n\n\"Eh? What plans are those?\" Understanding dawns with a sudden grin. \"Oh yes. The plans we discussed. I hope my own input was useful.\"\n\n\"Invaluable, my lord.\"\n\nHe arranges an audience with the Sultan and also pays you 50 dinars as a reward for letting the Sultan think that the plan came from both of you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 50);
    }

    int Continue(Character::Base &player) { return 193; }
};

class Story372 : public Story::Base
{
public:
    Story372()
    {
        ID = 372;

        Image = "images/filler4.png";

        Text = "The pirate leader wore a BLACK JEWEL on a chain around his neck. The captain of marines hands it to you. \"Perhaps you'd like to have this as a keepsake,\" he suggests. \"We have to take the rest of the booty back to the Sultan, of course.\"\n\nWhen you return to Cairo, the Sultan is overwhelmed with gratitude. \"Those pirates had been bleeding the city dry,\" he says. \"You are our saviour. This reward is hardly enough to express my thanks. On your future travels, always remember that there is a welcome here for you in Cairo.\"\n\nYou RECEIVED 1000 dinars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 1000);

        Take = {Item::BLACK_JEWEL};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 349; }
};

class Story373 : public Story::Base
{
public:
    Story373()
    {
        ID = 373;

        Text = "At dawn the next day, a sheath of darkness suddenly covers the burnished edge of the rising sun. The roaring wind hits only moments later, bringing with it dense clouds of stinging sand. The storm blots out all daylight. Sheltering your eyes, you grab the halter of the nearest camel to keep from getting lost. Then you realize you have the leading camel. It is up to you to decide which route to take.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head straight into the wind", 36));
        Choices.push_back(Choice::Base("Bear left", 82));
        Choices.push_back(Choice::Base("Lead the camels to the right", 59));

        Controls = Story::Controls::STANDARD;
    }
};

class Story374 : public Story::Base
{
public:
    Story374()
    {
        ID = 374;

        Text = "You scramble across the chamber, narrowly avoiding the Lord's blade as it slices through the air behind you, and dive into the jar.\n\nAfter a moment, his face appears above you. He wears a predatory smile as he says: \"You're cornered in your bolt-hole, little mouse. Let that be your final resting place, then.\"\n\nSand pours magically from his hands, filling the jar and smothering you. There is no escape.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story375 : public Story::Base
{
public:
    Story375()
    {
        ID = 375;

        Image = "images/port-of-suhar.png";

        Text = "You sail on to Basra and beyond, now leaving the river and entering open sea. Crossing the Persian Gulf as far as the Straits of Hormuz takes a week, in weather as serene as an idyll from the ancient epics. \"But wait till we're on the ocean,\" mutters one of the sailors. \"We'll earn our pay then.\"\n\nThe glittering port of Suhar lies a day's sailing down the coast from the straits. Here the ship will take on supplies for the long ocean voyage. You have the opportunity to stroll through the market and examine the goods on offer. You may purchase any of the following that you have money for: WATER BOTTLE, MIRROR, WHISTLE, GLOVES, and HAWK.";

        Bye = "You head back to the harbour.";

        Choices.clear();

        Controls = Story::Controls::SHOP;
    }

    void Event(Character::Base &player)
    {
        Shop = {{Item::WATER_BOTTLE, 5}, {Item::MIRROR, 20}, {Item::WHISTLE, 3}, {Item::GLOVES, 5}, {Item::HAWK, 20}};
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::BLACK_JEWEL}))
        {
            return 279;
        }
        else
        {
            return 301;
        }
    }
};

class Story376 : public Story::Base
{
public:
    std::string PreText = "";

    Story376()
    {
        ID = 376;

        Choices.clear();
        Choices.push_back(Choice::Base("Go to pray in the holy city", 101));
        Choices.push_back(Choice::Base("You can see Hakim's point", 123));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You stagger on, tortured by hunger and thirst every moment you are awake. Your sleep is a fever haunted by strange fugitive visions.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        Character::LOSE_ALL(player);

        if (player.Life > 0)
        {
            PreText += "\n\nYou fall to your knees in tearful thanks when at long last you see the walls and spires of a city in the distance. \n\n\"It is Mecca!\" says Rahman, the scribe who keeps Hakim's accounts. \"God be praised for His mercy. All of you, cast off your travelling clothes and prepare to enter the holy city. We must give thanks for our deliverance from the wilderness.\"\n\n\"Not so fast,\" says Hakim. \"We'll stop long enough to fill the waterskins, but if any of you want to get pious you'll have to do it on the way home. I'm in a hurry to get these goods to Cairo market, and I can't afford to dally around here for days on end.\"";
        }

        Text = PreText.c_str();
    }
};

class Story377 : public Story::Base
{
public:
    Story377()
    {
        ID = 377;

        Text = "You approach the tower and walk all around it. There is no way in. Looking up, you see a balcony surrounding the domed turret. But the walls are smooth and sheer. You doubt if a lizard would find enough purchase to climb it.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::AGILITY, Skill::Type::CUNNING}) && Character::VERIFY_ITEMS_ANY(player, {Item::HAWK, Item::INDIAN_ROPE}))
        {
            Choices.push_back(Choice::Base("Use a HAWK", 244, {Item::HAWK}));
            Choices.push_back(Choice::Base("Use an INDIAN ROPE", 334, {Item::INDIAN_ROPE}));
        }
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::AGILITY, Skill::Type::CUNNING}))
        {
            return 221;
        }
        else
        {
            return 311;
        }
    }
};

class Story378 : public Story::Base
{
public:
    Story378()
    {
        ID = 378;

        Text = "Strange stories are told about the Sultan of Nishapur. He is said to be a sorcerer who drowned his elder brother in a vat of black dye, then flayed the skin to make a covering for his sword. Learning spells that could command even the angels, he placed himself in a deep sleep during which a messenger came and cut out his eye with a silver dagger. The messenger -- apparently an angel -- bore the eye up to heaven, where it witnessed marvels beyond the limits of human experience. When the eye was brought back and replaced, the Sultan awoke with knowledge of secrets from before the dawn of time. The gaze of the eye had become so terrible, however, that it slew any who looked into it. So it was that from that day on the Sultan has always worn a mask, and the women of his harem are always blinded.\n\nThat, at least, is the story.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 398; }
};

class Story379 : public Story::Base
{
public:
    Story379()
    {
        ID = 379;

        Text = "Touching your lips, you bow and say, \"Peace be upon you, O King. Your perceptive gaze has gleaned the truth. I was cursed by a powerful jinni never to know good fortune. No doubt that is why I now find myself standing in abject terror with all my friends slaughtered around me. There is only one way to end this curse.\"\n\n\"Yes?\" says the Sultan. The leather of his saddle creaks as he leans forward in curiosity.\n\n\"I must be slain. Then my curse will pass to those who kill me.\" You look around at the band of knights, suddenly falling to your knees and wailing, \"I can take no more misery! Kill me, I pray!\"\n\nA nervous look passes between them. \"This pitiful wretch may speak the truth, Majesty,\" they say to the Sultan.\n\nThere is silence behind the mask, then he says, \"Only God is wise in all things. Come.\"\n\nThey ride off, leaving you alone in the midst of the carnage.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story380 : public Story::Base
{
public:
    Story380()
    {
        ID = 380;

        Text = "Azenomei is as good as his word. After levitating up and unlocking the grille, he throws the slippers down to you. Soon you have joined him on the edge of the pit.\n\nGazing down into the foetid hole that has been your prison for the last week, you cannot suppress a shudder of disgust. \"I might have wasted away to a skeleton down there.\"\n\nHe claps you on the back. \"Don't think of it. We're free!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 358; }
};

class Story381 : public Story::Base
{
public:
    std::string PreText = "";

    Story381()
    {
        ID = 381;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "The blaring note of the horn builds in the air until the very walls of the citadel begin to shake. You sense the tremendous pressure of the sound forcing itself out from where you are standing. A moment later, the vast metal blocks of the ceiling are blown apart and the whole structure collapses around you.\n\n";

        if (!Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            Character::GAIN_LIFE(player, -3);

            PreText += "You LOSE 3 Life Point(s).";
        }
        else
        {
            PreText += "[LUCK] You are miraculously unscathed.";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nYou dig your way out of the debris. There is no sign of Azenomei -- he must have perished in the ruins of his bronze fortress.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 66; }
};

class Story382 : public Story::Base
{
public:
    Story382()
    {
        ID = 382;

        Text = "You know more tall tales than all the sailors of Suhar, more unlikely yarns than the storytellers of Basra, and more outright lies than every beggar in Baghdad. Within minutes the CAT'S TAIL has soared up out of sight among the clouds. You tell it a few more falsehoods for good measure, since you want the TAIL to stay extended long enough for you to get what you came for, then you rapidly climb up to the top of the pinnacle.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 325; }
};

class Story383 : public Story::Base
{
public:
    Story383()
    {
        ID = 383;

        Text = "You make your way hurriedly away from the palace by way of the deserted back streets. Your heart is thudding at the thought of your bold escapade -- but it is still a bitter heart, for you have achieved next to nothing. Jafar remains free to plague the realm with his wickedness, and your own personal grievance remains unpunished.\n\nYou know now that you cannot expect to right all wrongs in a single night. First you must make your fortune. Once you are rich, you will be able to get an audience with the Caliph and tell him everything. But how will you earn fame and fortune?";

        Choices.clear();
        Choices.push_back(Choice::Base("Join a merchant caravan", 183));
        Choices.push_back(Choice::Base("Go to sea and sail in search of exotic lands, as the legendary Sindbad once did", 160));

        Controls = Story::Controls::STANDARD;
    }
};

class Story384 : public Story::Base
{
public:
    std::string PreText = "";

    Story384()
    {
        ID = 384;

        Choices.clear();
        Choices.push_back(Choice::Base("Try to get away", 404));
        Choices.push_back(Choice::Base("Keep on fighting", 427));
        Choices.push_back(Choice::Base("Drop the SWORD and surrender", 2));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::JEWELLED_SWORD});

        PreText = "You OBTAINED a JEWELLED SWORD. It serves as a normal SWORD for the purpose of using [SWORDPLAY]; nonetheless you suspect it may prove useful in other ways too.\n\nYou raise it to parry Masrur's first attack. His blade strikes with an impact that makes the hilt shudder in your grip, sending a bone-wrenching jolt all down your arm. Your own sword is almost dashed aside by Masrur's great strength, and the blow cuts a narrow gash across your brow.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nAs he lunges again, you jump back, making the most of your greater speed.\n\n\"Be thankful I'm trying not to damage that PRECIOUS SWORD,\" he puffs as you circle nimbly around him. \"Otherwise I'd cut you in two where you stand.\"\n\nOut of the corner of your eye you see a silk-gowned figure emerge from the next room. It is the evil vizier, Jafar. \"You're getting old, Masrur,\" he says snidely. \"There was a time when you could deal with a little gutter stripling like that without breaking into a sweat.\"";
        }

        Text = PreText.c_str();
    }
};

class Story385 : public Story::Base
{
public:
    Story385()
    {
        ID = 385;

        Text = "You swap clothes. It feels odd to wear the impractical silken finery of a harem girl, instead of your travelling clothes. The woman slips out of the back of the kiosk and turns at the rail. \"Since you have helped me, it's only right I should reward you,\" she whispers. \"See the PRAYER-MAT there? It has the special property that, when unrolled, it always lies in the direction of Mecca. Take it with my blessing.\"\n\nShe lowers herself into the water and swims off. After an hour or so, one of the guards comes back to check the kiosk. He peers through the curtain, but does not notice anything amiss. You doze off, only to be woken in the first grey light of dawn by cries of anguish.\n\n\"What has happened to Sabira?\" one of the guards is saying. \"Who are you?\"\n\nYou decide not to disclose your full involvement in the woman's escape. \"I was swimming last night,\" you reply. \"I came across this barque moored in the river. You were all playing dice in the prow, but there was no woman here. I saw a pile of fine veils and silks, which I dressed myself in for fun. I suppose the swim must have exhausted me, though, because then I fell asleep.\"\n\nThe guards start to wail and tear their hair, distressed at the thought of the punishment in store for them. They take no further interest in you, so you quietly slip away and swim back to your own ship.\n\nYou OBTAINED a HAREM COSTUME.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::PRAYER_MAT, Item::HAREM_COSTUME});
    }

    int Continue(Character::Base &player) { return 375; }
};

class Story386 : public Story::Base
{
public:
    Story386()
    {
        ID = 386;

        Text = "The warriors lie motionless on the dusty floor. Letting out a long sigh of relief, you lower your bruised fists and go back to Yussuf, who is shaking in a heap. As you help him to his feet, he whispers, \"I'm sorry I wasn't any help.\" He is too ashamed to look you in the eye.\n\n\"God did not give courage to all men and women in equal measure,\" you reply. You clasp his shoulder, trying to rally his spirits. \"You have other fine qualities, my friend -- your good humour, your loyalty, and your love of life.\"\n\nHe nods slowly. Then, raising his head, he peers into the gloom at the end of the gallery. \"Are you sure they're beaten?\"\n\nThe taper gives little light. Taking it back to where you left your fallen foes, you see no sign of the bodies. You look all around, expecting them to leap out of the darkness, when Yussuf points to the mural. \"Look, it's changed.\"\n\nHe's right. All of the warriors in the picture now lie defeated. A single hero in simple modern-day clothing is shown striding among them, breaking the ancient idols. Yussuf leans close to inspect the mural. His voice is a mixture of puzzlement and awe as he says, \"The face on this figure -- it might almost be you.\"\n\nYou take a close look. Long centuries have dimmed the ancient pigments. \"No...\" you say at last, shaking your head. \"It couldn't be.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 52; }
};

class Story387 : public Story::Base
{
public:
    Story387()
    {
        ID = 387;

        Text = "Reaching the bath-house, the man steps back and politely motions for you to enter. You step into the entrance. Coming into cool gloom after the bright sunlight outside, for a moment you can see nothing. You sense a movement to one side, but before you can react a heavy cosh whacks down against your skull, and you are swallowed up by a deeper darkness.\n\nYou LOSE 1 Life Point.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 432; }
};

class Story388 : public Story::Base
{
public:
    Story388()
    {
        ID = 388;

        Text = "On the very instant that she takes the flower from your fingers, the cloud underfoot becomes no more solid than a wisp of mist. You give a scream, which the child matches with a peal of malevolent laughter as she watches you sink through the cloud. For less than a heartbeat you are surrounded in white haze, then you break through the bottom of the cloud and go plunging down to strike the water with numbing force.\n\nYou LOSE 6 Life Points.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -6);
    }

    int Continue(Character::Base &player) { return 280; }
};

class Story389 : public Story::Base
{
public:
    Story389()
    {
        ID = 389;

        Text = "In time, fair winds and fate carry you to safe berth in the port of Zeila. Here you bid your shipmates farewell, for their travels will take them back to Basra, while you have yet to find your fortune.\n\nNearby are carts loaded with a variety of goods. They are bound for the market, and you know that you have a good chance of a bargain if you buy anything here. You find the following items for sale: WATER BOTTLE, ANTIDOTE, SWORD, VEIL and CANDLE.";

        Choices.clear();

        Controls = Story::Controls::SHOP;
    }

    void Event(Character::Base &player)
    {
        Shop = {{Item::WATER_BOTTLE, 1}, {Item::ANTIDOTE, 60}, {Item::SWORD, 15}, {Item::VEIL, 2}, {Item::CANDLE, 3}};
    }

    int Continue(Character::Base &player) { return 149; }
};

class Story390 : public Story::Base
{
public:
    std::string PreText = "";

    Story390()
    {
        ID = 390;

        Image = "images/filler3.png";

        Bye = "You watch Jumail rush in and clobber the prone bodies of the guards for good measure before turning to free your captain.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Jumail starts burbling with fright, but at least he overcomes it enough to snatch up a shovel and start flailing at the guards. His blows are mostly ineffectual, but they provide enough distraction to give you some hope of victory.\n\nThe fight is brief and silent.\n\n";

        auto DAMAGE = -4;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -2;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 412; }
};

class Story391 : public Story::Base
{
public:
    Story391()
    {
        ID = 391;

        Text = "Your weapon has as much effect as a blade of grass. With a shrill laugh, the she-ghoul raises her arm to strike back. The cleaver falls, embedding itself in your skull, and blood-soaked darkness falls around you. Your adventure is at an end.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story392 : public Story::Base
{
public:
    Story392()
    {
        ID = 392;

        Text = "One of the Sultan's advisors, a wealthy man named Nizam, has a reputation for modesty and generosity. You wait until you see him approaching the mosque for evening prayer, and then take out a bowl with which you start washing the feet of the worshippers as they come up the mosque steps. Nizam pauses beside you, but instead of washing his feet you select a common labourer with toes as dirty as a camel's.\n\n\"Why do you wash this man's feet ahead of mine?\" Nizam asks. \"Are you unaware that I am one of the Sultan's personal friends?\"\n\nFrom the corner of your eye you see that he wears a half smile, which is an encouraging sign. You decide to press ahead with your ploy. \"God sees no difference in your feet, nor cares a whit less for this man's prayers than for yours. You may indeed have the ear of the Sultan, but do not be so prideful as to suppose this elevates you above other men.\"\n\nNizam stares open-mouthed at this, then gives a delighted chuckle. \"Never have I heard such insolence. It is most refreshing! Please do me the honour of coming to my house for supper.\"\n\nThat night you strike up a friendship with Nizam over several games of chess. As you depart, you mention casually that you have a plan for dealing with the Red Sea pirates. \"Perhaps it would be better if the Sultan heard it from you, though,\" you suggest. \"He'd never listen to a commoner like me.\"\n\n\"Nonsense,\" replies Nizam. \"How can you, of all people, think such a thing? It is your plan, and I would not dream of presenting it as my own. Tomorrow I shall take you into the palace and introduce you to the Sultan. You can tell him your plan in person.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 193; }
};

class Story393 : public Story::Base
{
public:
    Story393()
    {
        ID = 393;

        // Also in 486
        Image = "images/stone-slab.png";

        Text = "Guided either by intuition or long experience, you stick to the course the pirates were on when last seen.\n\n\"Surely they must be trickier than that?\" complains the first mate.\n\nYou shake your head. \"Not at all. Remember that no other vessel has been able to track them. They're confident of their ability to vanish into thin air, so why would they worry about pursuit?\"\n\nAt dusk you arrive at high cliffs rising at the edge of the sea. Carved into the side of the cliff are two ancient colossi with heads of lions. Between them is a vast stone slab.\n\n\"It may be a door,\" says the first mate, \"but I can't see any way of getting it open.\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE) && !Character::VERIFY_CODEWORDS(player, {Codeword::Type::SESAME}) && !Character::VERIFY_ITEMS(player, {Item::Type::JERICHO_HORN}))
        {
            Choices.push_back(Choice::Base("Use [MAGIC]", 440, Skill::Type::MAGIC));
            Choices.push_back(Choice::Base("Otherwise", 415));
        }
    }

    int Continue(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE) && !Character::VERIFY_CODEWORDS(player, {Codeword::Type::SESAME}))
        {
            return 457;
        }
        else
        {
            return 437;
        }
    }
};

class Story394 : public Story::Base
{
public:
    Story394()
    {
        ID = 394;

        Text = "\"Why should we pay any toll?\" you reply in a challenging voice. \"No man owns the desert.\"\n\nThe Bedouin leader makes a sweeping gesture with the point of his spear. \"These skies are the canopy of our tents. The sands are our rugs. The rocks, our cushions. Hence you must pay.\"\n\n\"Are we your enemies?\" you ask him. \"Have we caused you any harm?\" When he does not find a ready answer, you go on, \"No -- for, if we had, then you would have already struck us down, as honour demands.\"\n\n\"And so?\" he mutters darkly.\n\n\"You say the desert itself is your home. If we are not your enemies, we must be your guests. The law of hospitality forbids you to profit from us.\"\n\nThere is no sound at all for several seconds. Then, to your relief, the Bedouin dismount and lead their camels over. The chief's face is like a mask of granite as he says, \"Well spoken. I am abashed. I shall kill my camel for your meal, and here is water from my own flask.\"\n\nThe water tastes like the contents of a ditch, but you do not complain. After spending as short a time with the Bedouin as courtesy allows, you make your excuses and travel on into the west.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 218; }
};

class Story395 : public Story::Base
{
public:
    Story395()
    {
        ID = 395;

        Text = "You pretend that you are so frightened that you start mumbling to yourself. \"Oh woe, that a poor slave like myself should suffer such a fate! A curse on my proud master for sending me down to keep this mighty spirit busy while he escaped.\"\n\n\"What's that you say?\" demands the Lord of the Desert, pressing his ear to the curtain. \"Who is your master?\"\n\n\"The Defender of the Faith, Harun al-Rashid, Caliph of all the civilized world,\" you reply. \"His learned sages explained how they could outwit a senile god of ancient times by sending me, a mere slave, as lure for his quicksand trap.\"\n\n\"Senile!\" he roars. \"I'll turn the tables on them yet. Quickly, come forth.\" When he sees you hesitate, he adds, \"Come. What do I care for the life of a slave when I can have Harun and his advisors?\"\n\nHe pours gold from thin air into your hands. \"Return to the surface,\" he says. \"When Harun sees this loot, tell him you found an abandoned treasure-house beneath the earth. Greed will bring him into my clutches.\"\n\nHe opens the iron door and waves you through.\n\nYou RECEIVED 60 dinars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 60);
    }

    int Continue(Character::Base &player) { return 459; }
};

class Story396 : public Story::Base
{
public:
    Story396()
    {
        ID = 396;

        Text = "You leap up, vault over the soldier's lance, and land directly in the Sultan's path. His guards think you are an assassin. Two of them swing their swords, but panic makes them clumsy. Ducking under their attacks, you jump forward and seize the bridle of the Sultan's horse, jerking it to a halt.\n\nAngry soldiers surround you. The Sultan stares down, more astonished than frightened. Raising his hand to stay his guards from attacking, he says, \"I am a good enough judge of character to see you are no lunatic or zealot. Why did you risk your life to get to me?\"\n\n\"Your excellency, how else can a commoner speak to a king? I know a way to catch the Red Sea pirates.\"\n\nHe nods. \"I'll hear what you have to say.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 193; }
};

class Story397 : public Story::Base
{
public:
    std::string PreText = "";

    Story397()
    {
        ID = 397;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "You huddle together during the long chill night. Everyone is too frightened to speak. They do not even want to guess what the dwarf will do when he wakes up.\n\nAt sunrise, as a pool of gold spreads along the eastern sky, one of the shark men steps forward and touches his master's arm. Yawning floridly, the dwarf makes a great show of sitting up, stretching, and rubbing his eyes. \"I don't see any tower!\" he cries in feigned surprise. \"You haven't even touched the pile of rubble. Don't tell me you all fell asleep instead of getting on with the job?\"\n\n\"You stunted fiend!\" roars the captain, his fear welling up into black rage. He grabs his sword. \"Let us go this instant or by God you'll be a head shorter!\"\n\nThe dwarf purses his blobby little lips in distaste, then babbles a quick spell. A queasy feeling crawls through your flesh as you are struck by the evil magic.";

        if (!Character::VERIFY_ITEMS(player, {Item::Type::BLACK_JEWEL}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nThere is nothing you can do to stop yourself from being turned into a gasping fish, and you will end your adventures on the dwarf's dinner plate.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 419; }
};

class Story398 : public Story::Base
{
public:
    Story398()
    {
        ID = 398;

        Text = "The Sultan makes a soft clicking sound with his tongue. It is almost too faint to be heard, but it is the signal for his knights to begin their butchery. Riding forward, they slash and stab at the terrified donkey-handlers. Abdullah scrambles for his sword but is cut down in front of you.\n\nSo far you're unscathed.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stand and fight", 17));
        Choices.push_back(Choice::Base("Run off along the woodland path", 40));

        Controls = Story::Controls::STANDARD;
    }
};

class Story399 : public Story::Base
{
public:
    Story399()
    {
        ID = 399;

        Text = "The captain welcomes you aboard his ship. \"We are bound for Basra,\" he says. \"The journey should take less than a month. Are you from that part of the world yourself?\"\n\n\"From Baghdad,\" you say. \"I left to seek my fortune.\"\n\nHe laughs. \"Well, I doubt you'd find it here. Overall, my last trip has barely shown a profit.\"\n\n\"Not until I came aboard, presumably,\" you say with a rueful look at your purse.\n\nYou PAID 50 dinars.\n\nThe voyage starts well, but only two days out from the coast a sudden squall blows in from the north. \"It will be a rough ride,\" predicts the captain. \"Hang on tight.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, -50);
    }

    int Continue(Character::Base &player) { return 131; }
};

class Story400 : public Story::Base
{
public:
    Story400()
    {
        ID = 400;

        Image = "images/bedouin-tents.png";

        Text = "The merchant caravan leaves the city, heading out across the desert. The camels lope sedately along, refusing to be hurried. You trudge beside them on sands the colour of dried blood, gazing at dunes sculpted by the wind into patterns like snakeskin. The air is dry as flint.\n\nAfter several days you come in sight of a group of tents crouching in the shade of a mountainous sand dune. The Bedouin emerge to greet you, glancing with shame at their scrawny goats. \"Alas, we have almost nothing to offer you by way of hospitality,\" laments their chief. \"But take this bread and the stew of vegetable roots that I was about to share with my family.\"\n\nIf you accept, it will mean that the Bedouin themselves go hungry.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            Choices.push_back(Choice::Base("Eat the food they have set before you", 127));
            Choices.push_back(Choice::Base("Insist they keep it", 171));
        }
    }

    int Continue(Character::Base &player) { return 104; }
};

class Story401 : public Story::Base
{
public:
    Story401()
    {
        ID = 401;

        Text = "Azenomei lends you his bunch of keys. Donning the slippers, you rise up to the grille and soon have it unlocked. Perched on the edge of the pit, you take a gulp of clean air -- your first in over a week. \n\n\"Come on!\" hisses Azenomei's voice from the darkness of the pit. \"Toss the slippers down.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Do as he asks", 358));
        Choices.push_back(Choice::Base("Leave him where he is", 422));

        Controls = Story::Controls::STANDARD;
    }
};

class Story402 : public Story::Base
{
public:
    Story402()
    {
        ID = 402;

        Text = "Fleeing from the city with your hands pressed to your ears to shut out the terrible din of the fight, you return to the ship and tell them what you saw.\n\n\"What dreadful place have you brought us with your wizardry?\" laments the captain, pulling off his turban and tearing his hair.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 144; }
};

class Story403 : public Story::Base
{
public:
    Story403()
    {
        ID = 403;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAREM}))
        {
            return 4;
        }
        else
        {
            return 19;
        }
    }
};

class Story404 : public Story::Base
{
public:
    Story404()
    {
        ID = 404;

        Text = "As you look around, Masrur gives a roar and charges forward, raising his sword with both hands for a mighty cleaving blow.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::AGILITY, Skill::Type::LUCK}))
        {
            Choices.push_back(Choice::Base("Use a HAWK", 139, {Item::HAWK}));
            Choices.push_back(Choice::Base("Otherwise", 161));
        }
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 70;
        }
        else
        {
            return 116;
        }
    }
};

class Story405 : public Story::Base
{
public:
    Story405()
    {
        ID = 405;

        Text = "You are thrown into prison. This time there will be no escape. A stake is already being sharpened. Tomorrow at dawn you will be impaled, and your warnings against Jafar will just be put down to the frantic last gambit of a convicted criminal.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story406 : public Story::Base
{
public:
    Story406()
    {
        ID = 406;

        Text = "You dive off the parapet. From where the guards are standing, it looks as if you have simply jumped to your doom. You hear a gasp of horror escape their throats, then the clatter of footsteps as they run to look down.\n\nYou are in fact clinging to the gonfalon. Sliding down hastily, you swing to safety on the balcony and press back into the shadow of a leafy trellis. A moment later, a row of pale astonished faces appear at the edge of the roof above. \"The fool jumped -- must've been insane,\" says one guard.\n\n\"I don't call that insanity,\" says another grimly. \"Better a quick death than face the Caliph's torturers.\"\n\nThe captain of the guards peers down through the darkness. \"I can't see a body,\" he mutters, voice tinged with the first stirrings of doubt. \"You two, get down there and make sure of it.\"\n\nYou waste no more time. When no corpse is found, they'll scour the palace looking for you. By that time you mean to be long gone. Letting yourself in through the balcony window, you steal a brocade CLOAK and slip unnoticed past the guards on the gate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::CLOAK});
    }

    int Continue(Character::Base &player) { return 383; }
};

class Story407 : public Story::Base
{
public:
    Story407()
    {
        ID = 407;

        Text = "It is an easy climb up the cliffs, with many jutting rocks and clumps of grass for you to hang on to. Yussuf follows with much mumbling and grumbling under his breath. He thinks you are foolhardy, but he will not abandon you to face danger alone.\n\nReaching a ledge, you see a small cave where a spindly old man sits huddled beside a bowl of red glowing charcoal. A lurid light lies across his face as he shows you a long-toothed smile and says, \"Peace be upon you, my friends.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Greet him in return", 429));
        Choices.push_back(Choice::Base("First demand to be told what he is doing here", 448));

        Controls = Story::Controls::STANDARD;
    }
};

class Story408 : public Story::Base
{
public:
    Story408()
    {
        ID = 408;

        Text = "You retrace your steps, watching the taper burn steadily down. At last, when its light has dimmed to just a dying red ember and you are on the point of giving up hope, Yussuf gives a whoop of joy.\n\n\"Starlight!\" he cries, clasping your arm and dragging you along. \"We've found the way out!\"\n\nYou emerge onto the ledge above the river and lose no time returning to the ship. It seems as though you have been blundering through underground tunnels for hours, so you are surprised to find that no one on board even noticed you were missing.\n\nThe others listen as you tell your story over supper. The captain gives a gruff sceptical laugh and says, \"Bah, you fell asleep and dreamed this nonsense.\" But you can tell from the crew's faces that they believe you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 375; }
};

class Story409 : public Story::Base
{
public:
    Story409()
    {
        ID = 409;

        Image = "images/filler4.png";

        Text = "You set sail with the morning tide, steering under the magnificent crescent arch at the harbour mouth and onto the open expanse of the ocean. Sunlight skitters like strings of pearls in the azure clefts of the sea.\n\nFor a week you hug the coast, watching the fishing villages glide by. Gulls shriek and circle overhead, excited at the prospect of fish stirred up by your passage. You watch each day as the dusky olive-green groves of the Hadramaut gradually give way to the stern ochre cliffs of south-west Araby.\n\nYou RECOVER 1 Life Point.\n\nArriving at the port of Raysut, you learn of pirates who have been preying on shipping in the Red Sea. \"They swoop down without warning in black-sailed ships,\" a longshoreman tells you as he helps load your cargo.\n\n\"Why doesn't the Sultan of Cairo order his fleets against them?\" asks your captain.\n\n\"After their raids, they vanish like the dew in the gardens of Baghdad with the coming of dawn,\" vows a sailor who claims to have seen them. \"One minute we had only empty sea ahead, then they were there. I alone escaped to tell the tale.\"\n\n\"And how did you manage that?\" one of the crew asks him.\n\n\"Ah, there is a tale...\" begins the man.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay to hear his story", 453));
        Choices.push_back(Choice::Base("Do some shopping in the market", 350));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 1);
    }
};

class Story410 : public Story::Base
{
public:
    std::string PreText = "";

    Story410()
    {
        ID = 410;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "Azenomei's laughter is like the shriek of the desert wind. Taking up his SWORD, he leaps forward to match you blow for blow. Under your feet, red human blood soon mingles with the black ichor of the jinni's veins. You feel yourself weakening, but you are determined to fight to the death.";

        if (!Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}) && !Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nWithout combat skills you are spitted on Azenomei's blade and die writhing in agony.";
        }
        else
        {
            PreText += "\n\n";

            auto DAMAGE = -6;

            if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
            {
                DAMAGE = -3;

                PreText += "[SWORDPLAY] ";
            }
            else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
            {
                PreText += "[WRESTLING] ";
            }

            Character::GAIN_LIFE(player, DAMAGE);

            PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 89; }
};

class Story411 : public Story::Base
{
public:
    Story411()
    {
        ID = 411;

        Text = "You unroll the rug. A smell rises from it like rich old loam. When you see what was wrapped up inside, you have to clap your hand to your mouth to keep from crying out. It is a dead body with cracked yellow bones protruding from flesh that crumbles like dry brown clay. From the look of it, it must have lain in the grave for many years. The eye sockets stare up at you from the floor -- a grisly gaze that sends a shudder through your limbs.\n\nYou can hear the two men coming back.";

        Choices.clear();
        Choices.push_back(Choice::Base("[CUNNING] You have a strong stomach", 31, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Quickly roll up the rug and hide", 433));
        Choices.push_back(Choice::Base("Stride openly into the inner room", 8));
        Choices.push_back(Choice::Base("Cravenly sneak back to the ship", 258));

        Controls = Story::Controls::STANDARD;
    }
};

class Story412 : public Story::Base
{
public:
    Story412()
    {
        ID = 412;

        Text = "On the way down to the jetty, Captain Ibrahim tells you that the ancestral court kept asking about the nest of the rokh, the giant bird said to prey on elephants. \"I told them I wanted only to trade silk for ivory, but they'd have none of it. They seemed to think I was after the diamond eggs the rokh lays.\"\n\n\"DIAMOND? The chicks must have hard beaks.\"\n\nJumail presses the captain with questions. \"Where does it nest, Captain, this great bird? How can one reach the eggs? Are they truly made of DIAMOND?\"\n\n\"Its nest is somewhere to the west,\" says the captain with as much interest as if he were speaking about the shape of a bee's backside. \"As for your other questions, I know no more than the next man.\"\n\nBy now you have reached the river. Climbing aboard, the captain gives the order to cast off at once.\n\nYou gained the codeword KISMET.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});
    }

    int Continue(Character::Base &player) { return 346; }
};

class Story413 : public Story::Base
{
public:
    Story413()
    {
        ID = 413;

        Text = "Your fist slams into the side of her head. It is like hitting a slab of granite. As you recoil back, clutching your broken hand, she whips the cleaver round and lays open your stomach. You slump to the floor, aghast, and the witch begins to twist your entrails into sausages even before you are quite dead.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story414 : public Story::Base
{
public:
    std::string PreText = "";

    Story414()
    {
        ID = 414;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "By luck, that very afternoon the Sultan comes riding through the streets in a regal procession. His soldiers patrol the crowds lining the streets, making sure that everyone bows respectfully. You glance up to see the Sultan himself approaching on the back of a graceful chestnut mare whose harness glitters with jewels. For a moment you meet his gaze. He strikes you as a good man but a weary one, his thoughts no doubt constantly troubled by affairs of state.\n\nOne of the soldiers sees you looking up and jabs the butt of his lance towards you. \"You there, keep your face to the ground while the Sultan goes by.\"";

        if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAJJI}) && !Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            PreText += "\n\nYou are shoved roughly back into the gutter and the moment is lost; you will not get another chance.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAJJI}))
        {
            return 436;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 396;
        }
        else
        {
            return 349;
        }
    }
};

class Story415 : public Story::Base
{
public:
    Story415()
    {
        ID = 415;

        Text = "You send your men clambering up over the huge door, but they cannot find any way to open it. At last you are forced to admit defeat. You return to Cairo and report to the Sultan that the pirates' lair lies beyond an unbreachable stone portal.\n\nHe is obviously disappointed, but he puts a cheerful face on it. \"You found out more than any of my own agents were able to,\" he says. \"Perhaps I can find a wizard who can force the portal to open. Take this reward for your services.\"\n\nYou are given a bag containing 50 dinars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 50);
    }

    int Continue(Character::Base &player) { return 349; }
};

class Story416 : public Story::Base
{
public:
    Story416()
    {
        ID = 416;

        Text = "People in flowing black robes come out from the gardens of the oasis to welcome you. They bring pitchers of fresh water which you drain gratefully. Then you are led to the tents of their camp, beneath the wall of the ruined fort, and made comfortable on rugs and cushions.\n\nAfter so long in the desert, to be surrounded by swaying palms and trickling streams is like a visit to Paradise. You rest at the oasis for several days.\n\nYou RECOVER 1 Life Point.\n\nEventually, with reluctance, you load your camels and set out on the last leg of your journey. \"We have nearly reached the Red Sea coast,\" Hakim says as you walk beside him. \"The worst is behind us now. Although I cannot pretend the roads to Cairo are wholly safe, at least we'll not perish of hunger or thirst.\"\n\n\"Our route takes us close to Mecca,\" you reply. \"Out of gratitude for our safe deliverance, we should stop and make the pilgrimage.\"\n\nHakim clicks his tongue. \"Oh, another time, perhaps. On the way back. I really can't afford to waste time at Mecca. I've got all these wares to sell in Cairo, you see.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to convince him to stop at Mecca", 101));
        Choices.push_back(Choice::Base("Let the matter drop", 123));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 1);
    }
};

class Story417 : public Story::Base
{
public:
    Story417()
    {
        ID = 417;

        Text = "The jinni comes out of your RING, but when he learns of your predicament he shakes his head sadly. \"I can help you escape, O Weaver of Enchantments,\" he whispers, \"but then I would have to remain trapped here until the end of the world. The glyph above the alcove is the seal of Suleiman, and no spirit or demon can pass by it. That is why the Lord of the Desert cannot pursue you in here.\"\n\nAt this, the Lord of the Desert stops pacing and stands with his ear pressed to the curtain. \"What's that?\" he says. \"Talking to yourself, are you? Are you mumbling your prayers, you pious little mouse?\"\n\nYou can say nothing to the jinni without giving the game away.";

        Choices.clear();
        Choices.push_back(Choice::Base("Nod for him to proceed with whatever he has planned", 169));
        Choices.push_back(Choice::Base("(SWORD) Leap out of the alcove to confront the Lord of the Desert", 13, Choice::Type::ANY_ITEM, {Item::SWORD, Item::JEWELLED_SWORD}));
        Choices.push_back(Choice::Base("Confront the Lord of the Desert: use only your bare hands", 331));

        Controls = Story::Controls::STANDARD;
    }
};

class Story418 : public Story::Base
{
public:
    Story418()
    {
        ID = 418;

        Text = "You ask about the women who work at the palace and find one, by the name of Fohzia, who runs errands for the Sultan's wives and also performs songs and dances in his court. You approach her while she is buying perfume in the marketplace. Pretending that you once worked in a harem yourself, you soon strike up a friendship. You help her carry her purchases back from the market. Standing outside the palace, you give a long sigh and say, \"How pleasant it would be to look on the face of the Sultan. I have heard he is a handsome man with a voice like the music of a harp.\"\n\nFohzia laughs. \"In all honesty, people tend to say that sort of thing about kings and princes. You mustn't take it too seriously.\"\n\n\"How knowledgeable you are, friend of my heart. Working in a harem has made you wise.\"\n\n\"I thought you used to work in a harem yourself?\" she says with a frown.\n\n\"Er... yes, but it was only a little harem in a tiny town. Well, more a village than a town. Just a few tents, in fact. I'd love to see inside a proper palace.\"\n\nAfter a little more wheedling, Fohzia relents and smuggles you into the palace. You have to wait a few days, but at last your chance arrives. The Sultan comes to sit with his wives, and as Fohzia is about to sing for him you suddenly jump forward and kiss the floor at his feet, crying, \"Cast me out if you wish, O Dispenser of Justice, but first hear why I smuggled myself into your court.\"\n\nHe peers at you, then shrugs and smiles indulgently. \"Very well, I'll listen to your story. At least it will make a change from the usual evening of songs, sherbets and sweetmeats.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 193; }
};

class Story419 : public Story::Base
{
public:
    Story419()
    {
        ID = 419;

        Text = "Your companions are all turned into fishes, but the black jewel deflects the spell so that you are not affected. \n\nThe dwarf frowns and mutters a protective rune. \"Incredible! No one has ever resisted my sorcery before.\"\n\nA bold bluff is your only chance. Taking a menacing step forward, you wave your hands in a meaningless but cryptic gesture. \"I am the High Adept of the Fire Wizards,\" you say angrily. \"How dare you cast your petty little spells at me, you gnarled lump of flesh! Now I shall send you shivering down to hell in a blast of fulminous flame.\"\n\n\"Wait, supreme one!\" he says, quailing. \"I did not realize! Forgive your wretched servant!\"\n\nYou look back at the fish thrashing around on the turf. \"Withdraw the spell. Restore my servants to their true shape and I may be lenient.\"\n\nHe hastily does so. As Captain Ibrahim and the rest go aboard the ship, the dwarf sidles over and says: \"May I ask what brought you here, O Worker of Miracles?\"\n\n\"We seek great treasures of ancient times. Do you know of such?\"\n\n\"There is the rokh's DIAMOND egg,\" he says. \"Its nest is at the head of the Nile, I believe. It would be a dangerous feat to steal it, though.\"\n\n\"Not for one of my power.\"\n\nYou dismiss the dwarf with a wave of your hand and stride up the gangplank. As the ship gets under sail, you stand in the stern, looking every inch the imperious wizard you pretend to be. Only when the uncharted isle has dropped below the horizon do you allow yourself to relax. Your sigh of relief is drowned out by the crew's cheers.\n\nThe BLACK JEWEL is cracked and clouded now that its power is used up.\n\nThe next few days pass uneventfully. You have not spotted any other vessels until a ship drifts into view one afternoon. Her sails are furled and there is no reply to your shouts. As you come alongside, you see the reason. The deck is strewn with corpses.\n\nYou gained the codeword KISMET.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::BLACK_JEWEL});

        Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});
    }

    int Continue(Character::Base &player) { return 356; }
};

class Story420 : public Story::Base
{
public:
    Story420()
    {
        ID = 420;

        Text = "At a signal from the masked Sultan, his knights ride forward and start to put Abdullah and the others to the sword. You quake in horror, fearing they will notice you at any moment.";

        Choices.clear();
        Choices.push_back(Choice::Base("[ROGUERY] Sneak off", 154, Skill::Type::ROGUERY));
        Choices.push_back(Choice::Base("Try your [LUCK]", 461, Skill::Type::LUCK));
        Choices.push_back(Choice::Base("You have neither of those skills", 79));

        Controls = Story::Controls::STANDARD;
    }
};

class Story421 : public Story::Base
{
public:
    Story421()
    {
        ID = 421;

        Text = "You loiter for a while in the marketplace, pretending to take note of the prices but making no purchase. After a while you wander away and sit in a thoughtful posture on the edge of a fountain. It is not long before a merchant approaches and strikes up a conversation. At first he talks of trifling matters, but at last a keen look comes into his eye and he says, \"Unless I am mistaken, you have been scouting out the market prices.\"\n\nYou adopt a smile that suggests grudging admiration. \"You are very perceptive. I have come here ahead of my master, who has three ships full of goods to sell. But he knows that as soon as people see he is a wealthy man, the asking prices will go up. Hence I am here to make purchases on his behalf.\"\n\nThe merchant licks his lips. \"Hmm. Well, what is your master interested in buying, if I may ask?\"\n\nYou take a sidelong glance at the stall the merchant was sitting in. \"He hopes to buy amber, which is in short supply back in Baghdad at the moment. Do you know anyone I could suggest he talks to?\"\n\nThe merchant throws up his hands in delight. \"What a coincidence! I myself trade in amber, and my prices are very reasonable.\" \n\n\"Well, as to that...\" You rub your jaw. \"I'd have to look around the market a bit more.\"\n\nHe takes out a bag of gold and presses it into your hands. \"Take my word for it. Just tell your master to come to Hisham al-Din -- that's me.\"\n\nYou nod sagely, assuring him you will do as he asks, and stroll away from the marketplace. The bribe he gave you is 200 dinars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 200);
    }

    int Continue(Character::Base &player) { return 399; }
};

class Story422 : public Story::Base
{
public:
    Story422()
    {
        ID = 422;

        Text = "How can you know who to trust? Leaving Azenomei to fend for himself, you hasten away across the courtyard.\n\nYou OBTAINED a BUNCH OF KEYS.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::BUNCH_OF_KEYS});
    }

    int Continue(Character::Base &player) { return 223; }
};

class Story423 : public Story::Base
{
public:
    Story423()
    {
        ID = 423;

        Text = "You seize a candelabrum and raise it above your head. Azenomei looks up at the last moment, his mouth opening to start a spell. He is too late. The candelabrum falls, breaking open his skull.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 89; }
};

class Story424 : public Story::Base
{
public:
    Story424()
    {
        ID = 424;

        Text = "You turn the key and the lock drops from Ayisha's shackles. She springs up at once with a cry of delight. \"Excellent! Now we can return home.\"\n\n\"And we must make all speed. I have to warn the Caliph about his evil vizier, Jafar, who has been plotting to overthrow him.\"\n\nShe nods thoughtfully. \"I believe it was Jafar who summoned the jinni to abduct me. Prepare yourself...\"\n\nRaising her hands and chanting the words of a spell, she conjures another whirlwind that whisks the two of you halfway across the world in the blink of an eye. As the wind dies down, you stagger giddily out of the vortex to see that you are now in the Caliph's throne room. Jafar is also here, and his look of astonishment is soon replaced by one of outright hatred when he sets eyes on your face.\n\nAyisha kisses the Caliph. \"Father, I have returned.\"\n\nThe Caliph is almost speechless with amazement. \"My heart is brimming with joy. But, Ayisha, who is this you've brought with you?\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 477; }
};

class Story425 : public Story::Base
{
public:
    Story425()
    {
        ID = 425;

        Image = "images/ghouls.png";

        Text = "The door is thrown open and you are dragged inside. Your first impression is the stench. It is as vile as a charnel house, and your guts bubble in turmoil. The sight of the hut's occupants is even worse: a morbidly pallid old she-ghoul and her two sons with faces of doltish evil. One of them holds you while the other gives you a painful poke in the ribs and says, \"A fine morsel for the supper-table.\"\n\n\"It's a mortal, Ma,\" says the other son.\n\n\"I can see that, you stupid boy,\" replies the mother with a voice like a goat being strangled. \"What's it doing here?\"\n\n\"Probably looking for the rokh's DIAMOND eggs,\" suggests the first son.\n\nShe shakes her head. \"No, wrong side of the Red Sea for that. Don't you boys listen to a word your old ma tells you? Oh well, get it trussed up. I'll stoke the fire.\"\n\nThey mean to eat you!\n\nYou gained the codeword KISMET.";

        Choices.clear();
        Choices.push_back(Choice::Base("Fight", 305));
        Choices.push_back(Choice::Base("Use [MAGIC]", 327, Skill::Type::MAGIC));
        Choices.push_back(Choice::Base("Try to trick your way out of this somehow", 348));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});

        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            Choices[0].Destination = 370;
        }
        else
        {
            Choices[0].Destination = 305;
        }
    }
};

class Story426 : public Story::Base
{
public:
    Story426()
    {
        ID = 426;

        Text = "The chamberlain returns and leads you down a long corridor to the throne room. Here the Caliph is sprawled on thick cushions, occasionally plucking a sweetmeat from the tray at his elbow.\n\nJafar is also here, and you sense his glare of hatred out of the corner of your eye, but you ignore him. Bowing to the Caliph, you say, \"O Prince of the Faith, I have travelled far and endured many hardships in order to warn you of the danger that threatens you.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 477; }
};

class Story427 : public Story::Base
{
public:
    Story427()
    {
        ID = 427;

        Text = "How will you press on with your attack?";

        Choices.clear();
        Choices.push_back(Choice::Base("Keep your guard up", 297));
        Choices.push_back(Choice::Base("Forget about parrying and just fight furiously in an attempt to force Masrur back", 276));

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            return 161;
        }
        else
        {
            return -1;
        }
    }
};

class Story428 : public Story::Base
{
public:
    Story428()
    {
        ID = 428;

        Text = "Your jinni emerges from the ring in a swirl of purple smoke. A single disdainful sweep of his gleaming eyes tells him what is going on. \"Shall I bring you armour and a hero's blade, that you may fight these snapping curs, esteemed one?\" he suggests in a voice like breaking rocks.\n\n\"I don't have the time for such nonsense,\" you reply curtly. \"Whisk me to the gatehouse roof, yonder.\"\n\nHe raises eyebrows like tufts of dried moss. \"You wish to flee? To turn tail and run from those puny wretches? Where is your bold heart?\"\n\n\"In my chest, where I'd like it to remain.\" The guards are just a few paces away. You scream at the jinni, \"Do it now!\"\n\nIn a whoosh of air you are plucked from the rooftop, tumbled through empty air, and deposited unceremoniously on the battlements of the gatehouse. With a sour grunt of disapproval, the jinni curls back into your ring, leaving you to race down to street level before the guards can get around to the courtyard and intercept you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 383; }
};

class Story429 : public Story::Base
{
public:
    Story429()
    {
        ID = 429;

        Text = "\"And may you know the mercy and blessings of God, venerable one,\" you reply, touching your brow and bowing.\n\n\"Live a hundred years, if it be God's will!\" says Yussuf rather more fulsomely as he scrambles onto the ledge beside you. You can tell from the wild look in his eyes that he believes the old man to be a wizard or ifrit.\n\nThe strange old man nods, the light of the coals sketching him like a figure of blood against the shadows. \"You have spoken well,\" he says, \"and now I shall speak. You see this cave? Within it are three treasures. Many have sought these treasures, and now their bones are the sand under our feet.\"\n\nYou kneel beside him. Your blood is quickened with excitement. \"You seem to know something more,\" you prompt him.\n\n\"I know much. I know how the treasure may be reached. There are three obstacles. The first is a hall of one-eyed monsters. Merely to look upon them means death. Next comes the gallery of warriors whom no weapon can harm. Swords they spurn, clubs cause them no concern -- \"\n\n\"What about knives?\" puts in Yussuf.\n\n\"Knives?\" The old man shakes his head. \"No good. Lastly there is the causeway where the light of hope can only bring doom.\" \n\nThere is a long moment of silence while you consider what the old man has told you. Yussuf, seeing the look in your eyes, grabs your arm imploringly. \"No, I beg you. It would be suicide! Forget this talk of treasure, and let's be on our way.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Return to the ship", 375));
        Choices.push_back(Choice::Base("Enter the cave", 483));

        Controls = Story::Controls::STANDARD;
    }
};

class Story430 : public Story::Base
{
public:
    Story430()
    {
        ID = 430;

        Text = "Quelling a shiver of nervousness, you begin the long descent. Yussuf watches you with a queasy look, then follows on his bottom, sliding carefully from step to step. You think he is being unnecessarily timid -- until your foot slips on the dank stone and you almost fall headlong. Then you too opt for the undignified but safer means of descent.\n\nYou soon lose sight of the tunnel mouth above. Now you feel as though you are suspended in a black void. You are uncomfortably aware of the long drop on either side, and the staircase seems narrower than ever.\n\nYou hear something that makes the hairs rise at the back of your neck. It is a soft ragged flapping. Dimly you can see shapes gliding down out of the dark recesses above. The forms are indistinct, but you see the faceted jewel-like glint of their predatory eyes.\n\n\"They're attracted by the light,\" you call back to Yussuf.\n\nThere is a moment as your words sink in. \"But -- but I can't put it out,\" he wails. \"Then we'd have to descend in pitch darkness.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Insist that he snuffs out the taper", 449));
        Choices.push_back(Choice::Base("Agree that it would be certain death", 5));

        Controls = Story::Controls::STANDARD;
    }
};

class Story431 : public Story::Base
{
public:
    Story431()
    {
        ID = 431;

        Text = "You set sail with the morning tide, passing under the magnificent crescent arch at the harbour mouth and onto the open expanse of the ocean. Sunlight skitters like strings of pearls in the azure clefts of the sea. Braced with one hand on the rail and the other on the main halyard, you suck the fresh salt-laced air into your lungs and gaze keenly into the east, where your destiny awaits.\n\nSix days out from Suhar, the lookout reports an island with white cliffs a few points off the port bow. The captain studies his charts and then looks up with a piqued expression. \"No such isle is marked here,\" he says. \"I wonder if it's worth investigating?\"\n\nYou can tell that the captain is torn between curiosity and the desire to get his cargo to the Indies without delay.";

        Choices.clear();
        Choices.push_back(Choice::Base("Encourage him to put in at the uncharted island", 75));
        Choices.push_back(Choice::Base("Urge him to keep your present course", 84));

        Controls = Story::Controls::STANDARD;
    }
};

class Story432 : public Story::Base
{
public:
    Story432()
    {
        ID = 432;

        Text = "You awaken to find you are in shackles. Others are also here, huddled on benches around a narrow room. Before you can question them to find out what is happening, the door is flung open and a tall bald fellow with muscles like iron bars strides in. Giving you a few rough strokes with a whip, he takes you by the arm and hauls you outside.\n\nThe hot dazzling sunlight makes you feel sick. Still dazed from the blow you took earlier, you stumble up onto a wooden platform where a slaver stands waiting. \"What am I bid for this strong young thing?\" he asks the crowd.\n\nThere is a confused babble of haggling, and before you can gather your wits to speak you have been sold to a merchant with sleek good looks that mark him out as an Egyptian. \"You will do to carry my wares back to Cairo,\" he says as he leads you away.\n\n\"There has been a mistake!\" you protest. \"I am no slave. I am a true believer, and whoever has shackled me thus has committed a crime against the laws of man and God.\"\n\nHe shows you a smile without humour. \"How often do you think I have heard that tale?\" he says. \"I'll tell you: every time I buy a new slave. Now come, wretch, and I'll assign you your chores.\"\n\nYou have LOST all your MONEY and all your BELONGINGS. You have only the SHACKLES on your wrists. It would give you no comfort. They announce to all who see you that you are a slave, and to try to escape now would only earn you a lingering death by crucifixion.\n\nYou gained the codeword MORDANT.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ALL(player);

        Character::GET_ITEMS(player, {Item::SHACKLES});

        Character::GET_CODEWORDS(player, {Codeword::Type::MORDANT});
    }

    int Continue(Character::Base &player) { return 400; }
};

class Story433 : public Story::Base
{
public:
    Story433()
    {
        ID = 433;

        Text = "You stay out of sight until the last rug has been carried in to the next room. Padding softly forward, you flit through the doorway with the swiftness of a shadow. The islanders are all on their knees with their foreheads pressed to the floorboards, facing away from you towards the far end of the room. One man at the back seems to sense something and turns for a quick glance, but by this time you are already out of sight behind a stout hardwood pillar.\n\n\"Why have you brought me here, you fiends?\" rings out a familiar growling voice.\n\nIt is Captain Ibrahim. You take a look out from behind the pillar. As your eyes adjust to the smoky torch-lit gloom, you see your captain standing against the far wall. To either side of him are ornately carved benches where tall silent figures sit as if in judgement. Each of the figures wears a rug wrapped around him and drawn up like a cowl across his head.\n\nNow another voice can be heard in the room. It is a dry hollow whisper, and the sound of it makes your skin crawl. It is coming from one of the figures on the bench. \"You stand before the Council of Ancestors. What plunder did you mean to take from our people?\"\n\n\"Plunder?\" demands Ibrahim, fighting to keep a nervous tremor out of his voice. \"I came not to plunder, but to trade. The Chinese silks and Indian spices in my ship's hold in return for gold and ivory.\"\n\nA soft murmuring ensues as the rug-cloaked figures lean their heads slightly together like seaweed fronds in a slow current. Other things are said, but too faintly for you to hear. Then the spokesman speaks again: \"We find you guilty. Tomorrow you shall be executed.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            return 77;
        }
        else
        {
            return 99;
        }
    }
};

class Story434 : public Story::Base
{
public:
    Story434()
    {
        ID = 434;

        Image = "images/filler2.png";

        Text = "With Jumail's help you soon overpower the other guard. Stepping over their senseless bodies, you approach the door of the hut. The lock gives way to several hard kicks. Captain Ibrahim is standing inside with his hands on his hips, beard jutting at a magisterial angle. \"About time you got here, you sons of sea cooks!\" he thunders. \"Now let's be off before the rest of those cursed natives arrive.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 412; }
};

class Story435 : public Story::Base
{
public:
    Story435()
    {
        ID = 435;

        Text = "You snatch up the wooden stick lying beside the door. As you throw yourself forward to strike, the she-ghoul's bony fingers are already closing around the handle of the meat cleaver. You stumble off-balance against the table. Everything seems to be in slow motion.";

        Choices.clear();
        Choices.push_back(Choice::Base("Lash her across the knuckles to stop her getting the cleaver", 455));
        Choices.push_back(Choice::Base("Wait until you are in position to give her a more solid blow", 33));

        Controls = Story::Controls::STANDARD;
    }
};

class Story436 : public Story::Base
{
public:
    Story436()
    {
        ID = 436;

        Text = "The Sultan sees your green turban, which marks you out as one who has undergone the pilgrimage to the holy city. Raising his hand to halt the procession, he dismounts and lifts you to your feet. \"I never pass a pilgrim without asking advice,\" he says with a warm smile. \"It is by God's grace that I sit on the throne of Cairo, after all.\"\n\nThis is one of those situations where it is worth coming straight to the point. You're not sure how long you could play the part of a pious savant anyhow. \"It is the lot of kings to be beset by many cares,\" you say, \"and no doubt you will find it so to the end of your days. But, O Sultan, I can rid you of at least one worry. I speak of the pirates of the Red Sea.\"\n\nHe gives you a keen thoughtful look. \"Speak on.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 193; }
};

class Story437 : public Story::Base
{
public:
    std::string PreText = "";

    Story437()
    {
        ID = 437;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You have heard the story of this ancient place. Addressing the two lion-headed statues, you call out, \"Meow, meow, open now!\"\n\nThe statues nod to show they understand. Your sailors wail in terror to see them flex their masonry muscles, but there is no danger. Now that you've spoken the magic formula, the statues are obedient to your will. They reach out and take hold of the door. There is a heavy grinding sound and slowly they slide it open, revealing a hidden cove massed with glittering treasures.\n\nThe pirates, halfway through unloading their latest plunder, are taken by surprise. They snatch up their swords and snarl defiantly as your marines swarm among them, but the outcome of the battle is in no doubt.\n\n";

        auto DAMAGE = -4;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JEWELLED_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
        {
            DAMAGE = -2;

            PreText += "[WRESTLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 372; }
};

class Story438 : public Story::Base
{
public:
    std::string PreText = "";

    Story438()
    {
        ID = 438;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "You soon regret the decision. All the waterskins are empty. Scanning the horizon, you see no sign of life -- just the endless shimmering waves of heat rising off bare dusty rock. Everyone walks stiffly, hollow eyes fixed on the far distance, knowing that to falter would spell their death. Even the camels move with a wearily splayed gait, heads hung low, morose expressions on their drooping mouths.\n\nNight falls. You LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou see a low dark cloud descend across the bright disc of the moon. \"God have mercy,\" groans Hakim through dry swollen lips. \"Not another sandstorm.\"";

            if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
            {
                Choices.push_back(Choice::Base("Press on towards the mysterious cloud", 354));
                Choices.push_back(Choice::Base("Skirt around it", 376));
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 310; }
};

class Story439 : public Story::Base
{
public:
    Story439()
    {
        ID = 439;

        Text = "Cupping your hands, you throw your voice to the far end of the chamber. The Lord of the Desert looks back over his shoulder as he hears muffled sounds outside the great iron-bound door.\n\n\"It must be a buried treasure vault,\" one voice apparently says.\n\n\"See if you can pick the lock, then,\" replies another.\n\nWith a perplexed frown, he strides over to the door and flings it open. Of course there is no one there. While his attention is distracted, you leave the alcove and hide yourself in one of the tall stone jars. Then you throw your voice back to the alcove you've just vacated, \"Hey, I'm getting peckish! Got anything to eat down here, you daft old goat?\"\n\nHis head snaps around with a look of fierce white fury. Stamping back to the curtain, he raises his sword and cries, \"Put out your hand, impertinent wretch! I'll slice you five fat sausages to fill your complaining belly.\"\n\nIn his anger, he forgot to lock the door. You slip out of the jar and tiptoe over to it, making sure to help yourself to a handful of gold before you go.\n\nYou OBTAINED 50 dinars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 50);
    }

    int Continue(Character::Base &player) { return 459; }
};

class Story440 : public Story::Base
{
public:
    Story440()
    {
        ID = 440;

        Text = "The jinni unfurls himself smokily from your ring, congealing like a blot of shadow in the low glancing rays of the setting sun. \"When you speak, I hear the voice of command,\" he says with careful courtesy.\n\n\"This door deters us. Open it.\"\n\nThe jinni looks at the portal, then turns a dubious glance from one massive statue to the other. Uncoiling his limbs in a long leap, he clings to the cliff beside one of the statues' ears and whispers something to it. When he springs back down to the deck, you glare at him and say, \"Well? You've heard my wish. Treat it as a command!\"\n\nThe jinni presses his hands together and gives an embarrassed half-bow. \"It is not so easy as that, O conjurer of marvels. The lion- headed sentinels will take umbrage if I break their door. Still, perhaps there is another way.\"\n\nThe first mate taps you on the shoulder. \"Do you mean to let this impertinent jinni tell you what you may wish for?\" he says. \"Show him who's in charge!\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Order the jinni to open the door", 460));
        Choices.push_back(Choice::Base("Ask him what else he can suggest", 196));
        Choices.push_back(Choice::Base("Dismiss him: use the Jericho HORN", 457, {Item::JERICHO_HORN}));
        Choices.push_back(Choice::Base("Use [FOLKLORE]", 437, Skill::Type::FOLKLORE));
        Choices.push_back(Choice::Base("You have the codeword SESAME", 437, {Codeword::Type::SESAME}));
        Choices.push_back(Choice::Base("Find another way to open the door", 415));

        Controls = Story::Controls::STANDARD;
    }
};

class Story441 : public Story::Base
{
public:
    Story441()
    {
        ID = 441;

        Text = "\"You are free to leave,\" declares the dwarf.\n\nCaptain Ibrahim has too much pride to let it go at that. \"In fact we never had any intention of landing at your cursed little island,\" he snorts. \"I had hoped it would be one of those fabled shores where lapiz lazuli streaks the beaches, or where the giant rokh lays its DIAMOND eggs.\"\n\nThe dwarf smiles at some private joke. \"There are no DIAMOND eggs here. You should seek the source of the Nile if that's what you're after.\"\n\nThe captain looks as though he would like to argue further. You drag him back to the ship and put to sea before the dwarf turns nasty. However, as the island dwindles into the distance, an ominous rumble shakes the sky. \"A storm in the offing,\" warns Yussuf, who is at the helm. \"We're in for a rough ride.\"\n\nYou gained the codeword KISMET.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::KISMET});
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            return 16;
        }
        else
        {
            return 131;
        }
    }
};

class Story442 : public Story::Base
{
public:
    std::string PreText = "";

    Story442()
    {
        ID = 442;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "";

        if (Character::VERIFY_ITEMS(player, {Item::Type::WATER_BOTTLE}))
        {
            Character::REFILL(player, Item::Type::WATER_BOTTLE);

            PreText += "You refill your WATER BOTTLE here. ";
        }

        PreText += "This city has nothing else to offer you. Passage on a ship back to Iraq will cost you 50 dinars.";

        Choices.clear();

        if (player.Money < 50)
        {
            PreText += " You don't have enough money and must resort to your skills.";

            Choices.push_back(Choice::Base("Resort to [STREETWISE]", 421, Skill::Type::STREETWISE));
            Choices.push_back(Choice::Base("Use [ROGUERY]", 481, Skill::Type::ROGUERY));
            Choices.push_back(Choice::Base("You have none of those skills", 461));
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 399; }
};

class Story443 : public Story::Base
{
public:
    std::string PreText = "";

    Story443()
    {
        ID = 443;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The chamberlain considers your request. ";

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAJJI}))
        {
            PreText += "He is moved by your piety and leads you to the throne room where the Caliph, waving asides Jafar's protests, beckons you forward.";
        }
        else
        {
            PreText += "The chamberlain is unmoved by your piety and summons the guards.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HAJJI}))
        {
            return 477;
        }
        else
        {
            return 405;
        }
    }
};

class Story444 : public Story::Base
{
public:
    Story444()
    {
        ID = 444;

        Text = "You find him in the highest chamber of the palace. He is younger than you imagined, and much less sinister in bearing than the fearsome wizards of folklore. He is clad all in blue, with an azure cloak over sky-coloured robes, rings of indigo and cobalt, sapphire-hued turban clasped by an actinic jewel. His eyes also are blue, though he is not pale-complexioned like a Christian.\n\nYou bow to him. \"I have you to thank for my health -- and perhaps for my life. May I know my benefactor's name?\"\n\nInstead of answering directly, he says, \"I am only an apprentice. Not the master of this palace, but its custodian.\" The blue eyes crinkle in a smile. \"You interest me. It's rare I can see into the future. The weave of Fate's tapestry is intricate and richly-dyed where it surrounds you.\"\n\n\"As to that, I cannot say. I have had my share of interesting adventures, certainly.\"\n\n\"And you have more to come. The curtain of time, opaque to other men, sometimes seems as a gauze veil to my eyes. I see you the victim of injustice. You will have sinister friends and unwitting foes. I see you ascending to the nest of the great rokh, the bird that lays eggs with DIAMOND shells. You'll ride on horseback through the air. Those are robes of honour that you wear. Or...\"\n\n\"Go on.\"\n\nHe shakes his head. \"I cannot tell if you will live. But I can give you a single gift that may help you.\" He brings forth a pair of embroidered SLIPPERS. \"Whoever wears these becomes weightless. You can use them to ascend to the rokh's lair.\"\n\nYou RECEIVED a pair of MAGIC SLIPPERS.";

        Bye = "Thanking the wizard, you rejoin the others. It is only after you've set sail that you realize you never found out his name.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::MAGIC_SLIPPERS});
    }

    int Continue(Character::Base &player) { return 389; }
};

class Story445 : public Story::Base
{
public:
    Story445()
    {
        ID = 445;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::LUCK))
        {
            return 97;
        }
        else
        {
            return 126;
        }
    }
};

class Story446 : public Story::Base
{
public:
    Story446()
    {
        ID = 446;

        Text = "You race up the stairs with the soldiers in hot pursuit. They think they have you, but you run out onto the terrace and vault down to the street below, leaving them to gawp like beached fishes. None of them cares to attempt such a daring leap. By the time they get back downstairs and out into the street, you are long gone.\n\nSheltering in a doorway, you watch a patrol of guards go tramping past. Your only chance now is to find the Caliph while he prowls the streets in disguise.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 182; }
};

class Story447 : public Story::Base
{
public:
    Story447()
    {
        ID = 447;

        Text = "There is nowhere you can run. Surrounded by the palace guards, you struggle valiantly but in vain. You are cut down under a dozen scything scimitars. As you flop weakly like a landed fish, blood spurting from your wounds, Jafar looks down at you with a rejoicing smile. You will take your hatred of him to the grave.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story448 : public Story::Base
{
public:
    Story448()
    {
        ID = 448;

        Text = "The old man rocks back on his heels and gives a peal of cackling laughter. \"It is unwise to forget your manners,\" he says. \"Now you'll learn a lesson.\"\n\nYou take a step forward, intending to seize him, but he throws his cloak over the flickering coals and you are plunged into sudden darkness. Yussuf blunders into you.\n\n\"Careful, or we might step off the ledge.\"\n\nYou hear him groping around in the dark. \"Er... I don't think we're on the ledge any more,\" he stammers.\n\n\"Then where are we?\"\n\n\"Here's a taper. Let me light it.\"\n\nThere is the clatter of stone on stone as he strikes a spark, then the taper catches. It gives only a faint nimbus of light, but that is enough to tell that you are in an underground cave. Yussuf starts to say something, but panic makes his voice catch in his throat. He can only tug your sleeve and point.\n\nYou turn, and in the dim light of the taper you see a horde of beasts that must have issued from the steaming pits of Hell.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 200; }
};

class Story449 : public Story::Base
{
public:
    Story449()
    {
        ID = 449;

        Text = "The old man rocks back on his heels and gives a peal of cackling laughter. \"It is unwise to forget your manners,\" he says. \"Now you'll learn a lesson.\"\n\nYou take a step forward, intending to seize him, but he throws his cloak over the flickering coals and you are plunged into sudden darkness. Yussuf blunders into you.\n\n\"Careful, or we might step off the ledge.\"\n\nYou hear him groping around in the dark. \"Er... I don't think we're on the ledge any more,\" he stammers.\n\n\"Then where are we?\"\n\n\"Here's a taper. Let me light it.\"\n\nThere is the clatter of stone on stone as he strikes a spark, then the taper catches. It gives only a faint nimbus of light, but that is enough to tell that you are in an underground cave. Yussuf starts to say something, but panic makes his voice catch in his throat. He can only tug your sleeve and point.\n\nYou turn, and in the dim light of the taper you see a horde of beasts that must have issued from the steaming pits of Hell.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 28;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            return 51;
        }
        else
        {
            return 73;
        }
    }
};

auto prologue = Prologue();
auto story001 = Story001();
auto story002 = Story002();
auto story003 = Story003();
auto story004 = Story004();
auto story005 = Story005();
auto story006 = Story006();
auto story007 = Story007();
auto story008 = Story008();
auto story009 = Story009();
auto story010 = Story010();
auto story011 = Story011();
auto story012 = Story012();
auto story013 = Story013();
auto story014 = Story014();
auto story015 = Story015();
auto story016 = Story016();
auto story017 = Story017();
auto story018 = Story018();
auto story019 = Story019();
auto story020 = Story020();
auto story021 = Story021();
auto story022 = Story022();
auto story023 = Story023();
auto story024 = Story024();
auto story025 = Story025();
auto story026 = Story026();
auto story027 = Story027();
auto story028 = Story028();
auto story029 = Story029();
auto story030 = Story030();
auto story031 = Story031();
auto story032 = Story032();
auto story033 = Story033();
auto story034 = Story034();
auto story035 = Story035();
auto story036 = Story036();
auto story037 = Story037();
auto story038 = Story038();
auto story039 = Story039();
auto story040 = Story040();
auto story041 = Story041();
auto story042 = Story042();
auto story043 = Story043();
auto story044 = Story044();
auto story045 = Story045();
auto story046 = Story046();
auto story047 = Story047();
auto story048 = Story048();
auto story049 = Story049();
auto story050 = Story050();
auto story051 = Story051();
auto story052 = Story052();
auto story053 = Story053();
auto story054 = Story054();
auto story055 = Story055();
auto story056 = Story056();
auto story057 = Story057();
auto story058 = Story058();
auto story059 = Story059();
auto story060 = Story060();
auto story061 = Story061();
auto story062 = Story062();
auto story063 = Story063();
auto story064 = Story064();
auto story065 = Story065();
auto story066 = Story066();
auto story067 = Story067();
auto story068 = Story068();
auto story069 = Story069();
auto story070 = Story070();
auto story071 = Story071();
auto story072 = Story072();
auto story073 = Story073();
auto story074 = Story074();
auto story075 = Story075();
auto story076 = Story076();
auto story077 = Story077();
auto story078 = Story078();
auto story079 = Story079();
auto story080 = Story080();
auto story081 = Story081();
auto story082 = Story082();
auto story083 = Story083();
auto story084 = Story084();
auto story085 = Story085();
auto story086 = Story086();
auto story087 = Story087();
auto story088 = Story088();
auto story089 = Story089();
auto story090 = Story090();
auto story091 = Story091();
auto story092 = Story092();
auto story093 = Story093();
auto story094 = Story094();
auto story095 = Story095();
auto story096 = Story096();
auto story097 = Story097();
auto story098 = Story098();
auto story099 = Story099();
auto story100 = Story100();
auto story101 = Story101();
auto story102 = Story102();
auto story103 = Story103();
auto story104 = Story104();
auto story105 = Story105();
auto story106 = Story106();
auto story107 = Story107();
auto story108 = Story108();
auto story109 = Story109();
auto story110 = Story110();
auto story111 = Story111();
auto story112 = Story112();
auto story113 = Story113();
auto story114 = Story114();
auto story115 = Story115();
auto story116 = Story116();
auto story117 = Story117();
auto story118 = Story118();
auto story119 = Story119();
auto story120 = Story120();
auto story121 = Story121();
auto story122 = Story122();
auto story123 = Story123();
auto story124 = Story124();
auto story125 = Story125();
auto story126 = Story126();
auto story127 = Story127();
auto story128 = Story128();
auto story129 = Story129();
auto story130 = Story130();
auto story131 = Story131();
auto story132 = Story132();
auto story133 = Story133();
auto story134 = Story134();
auto story135 = Story135();
auto story136 = Story136();
auto story137 = Story137();
auto story138 = Story138();
auto story139 = Story139();
auto story140 = Story140();
auto story141 = Story141();
auto story142 = Story142();
auto story143 = Story143();
auto story144 = Story144();
auto story145 = Story145();
auto story146 = Story146();
auto story147 = Story147();
auto story148 = Story148();
auto story149 = Story149();
auto story150 = Story150();
auto story151 = Story151();
auto story152 = Story152();
auto story153 = Story153();
auto story154 = Story154();
auto story155 = Story155();
auto story156 = Story156();
auto story157 = Story157();
auto story158 = Story158();
auto story159 = Story159();
auto story160 = Story160();
auto story161 = Story161();
auto story162 = Story162();
auto story163 = Story163();
auto story164 = Story164();
auto story165 = Story165();
auto story166 = Story166();
auto story167 = Story167();
auto story168 = Story168();
auto story169 = Story169();
auto story170 = Story170();
auto story171 = Story171();
auto story172 = Story172();
auto story173 = Story173();
auto story174 = Story174();
auto story175 = Story175();
auto story176 = Story176();
auto story177 = Story177();
auto story178 = Story178();
auto story179 = Story179();
auto story180 = Story180();
auto story181 = Story181();
auto story182 = Story182();
auto story183 = Story183();
auto story184 = Story184();
auto story185 = Story185();
auto story186 = Story186();
auto story187 = Story187();
auto story188 = Story188();
auto story189 = Story189();
auto story190 = Story190();
auto story191 = Story191();
auto story192 = Story192();
auto story193 = Story193();
auto story194 = Story194();
auto story195 = Story195();
auto story196 = Story196();
auto story197 = Story197();
auto story198 = Story198();
auto story199 = Story199();
auto story200 = Story200();
auto story201 = Story201();
auto story202 = Story202();
auto story203 = Story203();
auto story204 = Story204();
auto story205 = Story205();
auto story206 = Story206();
auto story207 = Story207();
auto story208 = Story208();
auto story209 = Story209();
auto story210 = Story210();
auto story211 = Story211();
auto story212 = Story212();
auto story213 = Story213();
auto story214 = Story214();
auto story215 = Story215();
auto story216 = Story216();
auto story217 = Story217();
auto story218 = Story218();
auto story219 = Story219();
auto story220 = Story220();
auto story221 = Story221();
auto story222 = Story222();
auto story223 = Story223();
auto story224 = Story224();
auto story225 = Story225();
auto story226 = Story226();
auto story227 = Story227();
auto story228 = Story228();
auto story229 = Story229();
auto story230 = Story230();
auto story231 = Story231();
auto story232 = Story232();
auto story233 = Story233();
auto story234 = Story234();
auto story235 = Story235();
auto story236 = Story236();
auto story237 = Story237();
auto story238 = Story238();
auto story239 = Story239();
auto story240 = Story240();
auto story241 = Story241();
auto story242 = Story242();
auto story243 = Story243();
auto story244 = Story244();
auto story245 = Story245();
auto story246 = Story246();
auto story247 = Story247();
auto story248 = Story248();
auto story249 = Story249();
auto story250 = Story250();
auto story251 = Story251();
auto story252 = Story252();
auto story253 = Story253();
auto story254 = Story254();
auto story255 = Story255();
auto story256 = Story256();
auto story257 = Story257();
auto story258 = Story258();
auto story259 = Story259();
auto story260 = Story260();
auto story261 = Story261();
auto story262 = Story262();
auto story263 = Story263();
auto story264 = Story264();
auto story265 = Story265();
auto story266 = Story266();
auto story267 = Story267();
auto story268 = Story268();
auto story269 = Story269();
auto story270 = Story270();
auto story271 = Story271();
auto story272 = Story272();
auto story273 = Story273();
auto story274 = Story274();
auto story275 = Story275();
auto story276 = Story276();
auto story277 = Story277();
auto story278 = Story278();
auto story279 = Story279();
auto story280 = Story280();
auto story281 = Story281();
auto story282 = Story282();
auto story283 = Story283();
auto story284 = Story284();
auto story285 = Story285();
auto story286 = Story286();
auto story287 = Story287();
auto story288 = Story288();
auto story289 = Story289();
auto story290 = Story290();
auto story291 = Story291();
auto story292 = Story292();
auto story293 = Story293();
auto story294 = Story294();
auto story295 = Story295();
auto story296 = Story296();
auto story297 = Story297();
auto story298 = Story298();
auto story299 = Story299();
auto story300 = Story300();
auto story301 = Story301();
auto story302 = Story302();
auto story303 = Story303();
auto story304 = Story304();
auto story305 = Story305();
auto story306 = Story306();
auto story307 = Story307();
auto story308 = Story308();
auto story309 = Story309();
auto story310 = Story310();
auto story311 = Story311();
auto story312 = Story312();
auto story313 = Story313();
auto story314 = Story314();
auto story315 = Story315();
auto story316 = Story316();
auto story317 = Story317();
auto story318 = Story318();
auto story319 = Story319();
auto story320 = Story320();
auto story321 = Story321();
auto story322 = Story322();
auto story323 = Story323();
auto story324 = Story324();
auto story325 = Story325();
auto story326 = Story326();
auto story327 = Story327();
auto story328 = Story328();
auto story329 = Story329();
auto story330 = Story330();
auto story331 = Story331();
auto story332 = Story332();
auto story333 = Story333();
auto story334 = Story334();
auto story335 = Story335();
auto story336 = Story336();
auto story337 = Story337();
auto story338 = Story338();
auto story339 = Story339();
auto story340 = Story340();
auto story341 = Story341();
auto story342 = Story342();
auto story343 = Story343();
auto story344 = Story344();
auto story345 = Story345();
auto story346 = Story346();
auto story347 = Story347();
auto story348 = Story348();
auto story349 = Story349();
auto story350 = Story350();
auto story351 = Story351();
auto story352 = Story352();
auto story353 = Story353();
auto story354 = Story354();
auto story355 = Story355();
auto story356 = Story356();
auto story357 = Story357();
auto story358 = Story358();
auto story359 = Story359();
auto story360 = Story360();
auto story361 = Story361();
auto story362 = Story362();
auto story363 = Story363();
auto story364 = Story364();
auto story365 = Story365();
auto story366 = Story366();
auto story367 = Story367();
auto story368 = Story368();
auto story369 = Story369();
auto story370 = Story370();
auto story371 = Story371();
auto story372 = Story372();
auto story373 = Story373();
auto story374 = Story374();
auto story375 = Story375();
auto story376 = Story376();
auto story377 = Story377();
auto story378 = Story378();
auto story379 = Story379();
auto story380 = Story380();
auto story381 = Story381();
auto story382 = Story382();
auto story383 = Story383();
auto story384 = Story384();
auto story385 = Story385();
auto story386 = Story386();
auto story387 = Story387();
auto story388 = Story388();
auto story389 = Story389();
auto story390 = Story390();
auto story391 = Story391();
auto story392 = Story392();
auto story393 = Story393();
auto story394 = Story394();
auto story395 = Story395();
auto story396 = Story396();
auto story397 = Story397();
auto story398 = Story398();
auto story399 = Story399();
auto story400 = Story400();
auto story401 = Story401();
auto story402 = Story402();
auto story403 = Story403();
auto story404 = Story404();
auto story405 = Story405();
auto story406 = Story406();
auto story407 = Story407();
auto story408 = Story408();
auto story409 = Story409();
auto story410 = Story410();
auto story411 = Story411();
auto story412 = Story412();
auto story413 = Story413();
auto story414 = Story414();
auto story415 = Story415();
auto story416 = Story416();
auto story417 = Story417();
auto story418 = Story418();
auto story419 = Story419();
auto story420 = Story420();
auto story421 = Story421();
auto story422 = Story422();
auto story423 = Story423();
auto story424 = Story424();
auto story425 = Story425();
auto story426 = Story426();
auto story427 = Story427();
auto story428 = Story428();
auto story429 = Story429();
auto story430 = Story430();
auto story431 = Story431();
auto story432 = Story432();
auto story433 = Story433();
auto story434 = Story434();
auto story435 = Story435();
auto story436 = Story436();
auto story437 = Story437();
auto story438 = Story438();
auto story439 = Story439();
auto story440 = Story440();
auto story441 = Story441();
auto story442 = Story442();
auto story443 = Story443();
auto story444 = Story444();
auto story445 = Story445();
auto story446 = Story446();
auto story447 = Story447();
auto story448 = Story448();
auto story449 = Story449();

void InitializeStories()
{
    Stories = {
        &prologue, &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009,
        &story010, &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019,
        &story020, &story021, &story022, &story023, &story024, &story025, &story026, &story027, &story028, &story029,
        &story030, &story031, &story032, &story033, &story034, &story035, &story036, &story037, &story038, &story039,
        &story040, &story041, &story042, &story043, &story044, &story045, &story046, &story047, &story048, &story049,
        &story050, &story051, &story052, &story053, &story054, &story055, &story056, &story057, &story058, &story059,
        &story060, &story061, &story062, &story063, &story064, &story065, &story066, &story067, &story068, &story069,
        &story070, &story071, &story072, &story073, &story074, &story075, &story076, &story077, &story078, &story079,
        &story080, &story081, &story082, &story083, &story084, &story085, &story086, &story087, &story088, &story089,
        &story090, &story091, &story092, &story093, &story094, &story095, &story096, &story097, &story098, &story099,
        &story100, &story101, &story102, &story103, &story104, &story105, &story106, &story107, &story108, &story109,
        &story110, &story111, &story112, &story113, &story114, &story115, &story116, &story117, &story118, &story119,
        &story120, &story121, &story122, &story123, &story124, &story125, &story126, &story127, &story128, &story129,
        &story130, &story131, &story132, &story133, &story134, &story135, &story136, &story137, &story138, &story139,
        &story140, &story141, &story142, &story143, &story144, &story145, &story146, &story147, &story148, &story149,
        &story150, &story151, &story152, &story153, &story154, &story155, &story156, &story157, &story158, &story159,
        &story160, &story161, &story162, &story163, &story164, &story165, &story166, &story167, &story168, &story169,
        &story170, &story171, &story172, &story173, &story174, &story175, &story176, &story177, &story178, &story179,
        &story180, &story181, &story182, &story183, &story184, &story185, &story186, &story187, &story188, &story189,
        &story190, &story191, &story192, &story193, &story194, &story195, &story196, &story197, &story198, &story199,
        &story200, &story201, &story202, &story203, &story204, &story205, &story206, &story207, &story208, &story209,
        &story210, &story211, &story212, &story213, &story214, &story215, &story216, &story217, &story218, &story219,
        &story220, &story221, &story222, &story223, &story224, &story225, &story226, &story227, &story228, &story229,
        &story230, &story231, &story232, &story233, &story234, &story235, &story236, &story237, &story238, &story239,
        &story240, &story241, &story242, &story243, &story244, &story245, &story246, &story247, &story248, &story249,
        &story250, &story251, &story252, &story253, &story254, &story255, &story256, &story257, &story258, &story259,
        &story260, &story261, &story262, &story263, &story264, &story265, &story266, &story267, &story268, &story269,
        &story270, &story271, &story272, &story273, &story274, &story275, &story276, &story277, &story278, &story279,
        &story280, &story281, &story282, &story283, &story284, &story285, &story286, &story287, &story288, &story289,
        &story290, &story291, &story292, &story293, &story294, &story295, &story296, &story297, &story298, &story299,
        &story300, &story301, &story302, &story303, &story304, &story305, &story306, &story307, &story308, &story309,
        &story310, &story311, &story312, &story313, &story314, &story315, &story316, &story317, &story318, &story319,
        &story320, &story321, &story322, &story323, &story324, &story325, &story326, &story327, &story328, &story329,
        &story330, &story331, &story332, &story333, &story334, &story335, &story336, &story337, &story338, &story339,
        &story340, &story341, &story342, &story343, &story344, &story345, &story346, &story347, &story348, &story349,
        &story350, &story351, &story352, &story353, &story354, &story355, &story356, &story357, &story358, &story359,
        &story360, &story361, &story362, &story363, &story364, &story365, &story366, &story367, &story368, &story369,
        &story370, &story371, &story372, &story373, &story374, &story375, &story376, &story377, &story378, &story379,
        &story380, &story381, &story382, &story383, &story384, &story385, &story386, &story387, &story388, &story389,
        &story390, &story391, &story392, &story393, &story394, &story395, &story396, &story397, &story398, &story399,
        &story400, &story401, &story402, &story403, &story404, &story405, &story406, &story407, &story408, &story409,
        &story410, &story411, &story412, &story413, &story414, &story415, &story416, &story417, &story418, &story419,
        &story420, &story421, &story422, &story423, &story424, &story425, &story426, &story427, &story428, &story429,
        &story430, &story431, &story432, &story433, &story434, &story435, &story436, &story437, &story438, &story439,
        &story440, &story441, &story442, &story443, &story444, &story445, &story446, &story447, &story448, &story449};
}

#endif