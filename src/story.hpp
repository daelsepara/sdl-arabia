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
        PreText = "There is a clang as your sword strikes the floor, followed by an ominous hush as Masrur steps forward smiling and pins your arms behind your back. You are taken to the dungeons, stripped of everything you own, then hung in chains and tortured for several days.\n\nYou LOSE 2 Life Points.";

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

        Text = "Now that the danger is over, you find you are trembling in shock. You sit on the end of Ayisha's couch while you recover. \"Where did you learn sorcery?\"\n\n\"My old nurse taught me,\" she replies, smiling. \"Alas, she never told me any spell to undo these enchanted chains.\"\n\n\"There must be a key.\"\n\nAyisha nods. \"There is. It is in the nest of the giant bird known as the rokh. If you\"d agree to try and get it, I could send you there with another spell I know.\" She pauses and adds hesitantly, \"It would be dangerous, of course.\"";

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

        Text = "You go and shelter in a cave, after first checking that it isn't already occupied. A raw wind howls outside, but you are snug inside your woollen cloak. Even so, you get very little sleep after your horrific experience. Rising with the first silver light of the predawn, you head down out of the hills to join the others.";

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

        Text = "You explain to the old man that there has been a mistake. You are not the one who stole the Sultan'S ruby.\n\nSurprisingly, his answer to this is a thin wheeze of laughter. \"Not the Shadow, eh? I thought not. I doubt they'll ever catch that one.\"\n\n\"Who is the Shadow?\"\n\n\"The most daring of knaves. The rogue who purloined the jinn ring of Ala al-Din and the flying rug once owned by the Emir of Cordoba, as well as the crown of the infidel ruler Shah al Ma'in. He -- or she, for the Shadow is a figure veiled in mystery -- has vowed next to steal the diamond egg of the rokh.\"";

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

        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::SWORDPLAY, Skill::Type::WRESTLING}))
        {
            DAMAGE = -1;

            if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
            {
                PreText += "[SWORDPLAY] ";
            }

            if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
            {
                PreText += "[WRESTLING] ";
            }
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

        if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }
        else
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

        Text = "The guards burst into the room, only to find a dead body slumped on the cold marble floor. Shrugging, they sheathe their swords. Jafar pushes his way to the front and demands to know what is going on.\n\n\"The intruder committed suicide, it seems, lord,\" says the captain of the guard, indicating the trickle of poison on your lips.\n\nJafar hisses between his teeth. \"A pity. I\"d have liked to oversee the interrogation of this one.\"\n\nThe captain hides a flicker of disgust at Jafar's open cruelty. Turning away sharply, he says to the guards, \"Take this corpse to the burial-ground.\"\n\nYou are taken to the edge of the city and left in a small brick building beside the cemetery, there to await burial in the morning. When the guards have left, the jinni breathes the gust of life back into your lungs. Rubbing your stiff limbs, you get up and fix him with a sour frown. \"Why did you make them think I was dead?\"\n\nHe smiles -- at least, you think it's a smile. \"They\"re not going to kill you twice, are they?\"\n\n\"But why didn't you turn their swords to snakes? Or fill the room with choking fog? Or whisk me away to safety on a flying cloud?\"\n\n\"Oh, what are you complaining about?\" snaps the jinni. \"I got you out safely, didn't I?\" He becomes a twist of vapour that slowly flows back into your ring.\n\nAs you walk back from the graveyard, you consider that it might be wise to quit Baghdad for a while. The wild corners of the world are full of mystery and promise, and adventurers of olden times often returned from their travels laden with riches. If you could do the same, then you would be a better position to bring Jafar to justice. It only remains to decide your route.";

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

        if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }
        else
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

        Text = "The mysterious island drops astern and is lost to sight. For a day or so afterwards, the captain takes to stamping around the deck fretfully. \"I should have surveyed the isle, at least,\" he admits to you. \"It might have been one of those places spoken of in the old tales.\"\n\n\"Which tales are those?\"\n\n\"You know the ones! I\"ve heard tell of islands where the fruit is solid gold, where the streams give eternal life and the womenfolk are --\"\n\n\"Ah, I thought you meant the other tales.\" You take a sip of water from the barrel to conceal a smile. \"Stories of Sindbad's voyages -- islands inhabited by murderous cannibals, insane wizards, bloated giants and the like.\"\n\n\"Yes...\" says the captain thoughtfully. \"I expect I made the right decision, after all.\"\n\nA sailor breaks in on your conversation to point out a ship drifting ahead. Her sails are furled and there is no reply to your shouts. As you come alongside, you see the reason. The deck is strewn with corpses.";

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
            PreText += "\n\nIf you survive, you hear the guards\" shouts from above. You cannot lie flopping in agony on the ground. You must rise and flee for your life before they catch you.\n\nLimping painfully towards the gate you are intercepted by a sentry. Your heart sinks, but then you realise that he does not know what the commotion is all about. He stares past you at the soldiers rushing across the courtyard. \"What's going on?\" he asks.\n\n\"There\"s an assassin in the palace,\" you gasp through gritted teeth.\n\nThe sentry rushes off across the courtyard. Moving with all the speed your twisted ankle will allow, you slip out of the gate and duck into the shadows of a side street. Glancing back, you see the soldiers who were chasing you run out of the gate. They look around, confused, but none saw where you went. You have given them the slip.";
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

        Text = "Sparkling light appears from no obvious source. You see crystal pillars forming an alcove in the wall ahead of you. The old man whom you met on the ledge is here, dressed now in the white robes of a king of Old Persia. A black jewel shimmers at his throat. You stand in awe of the unknown as Yussuf slowly pads down the steps to join you.\n\n\"You have done well to come this far, and now you shall claim your reward,\" says the old man. \"Here are four treasures.\" He reaches into a gold-banded treasure chest and brings out a COPPER LAMP. \"This is the enchanted LAMP used by the hero Antar when he crept unseen through the harem of Sakhur the Jinni.\"\n\n\"How does it work?\" asks Yussuf.\n\n\"Merely light it, and while you hold it in your hands no-one can see you. But there is only a little of the magic oil left. Enough for a few minutes of invisibility at best.\" He puts the LAMP down and produces a coil of ROPE. \"This second treasure is a ROPE of distant India. On command it will rise straight into the air of its own accord -- a marvellous treasure for a rogue!\" He puts the ROPE aside and draws a TRUMPET out of the chest. \"And this is the horn which levelled the walls of Jericho in ancient times. Be warned, however, that to unleash its destructive force is perilous.\"\n\nHe stands with folded arms while you gaze on the treasures. \"How many can we take?\" asks Yussuf. \"Just one?\"\n\n\"One each!\" declares the old man.\n\nYussuf leaves it to you to decide.";

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

        Text = "You give orders for the merchantman's sailors to take your ship back to port, while your own crew come aboard and man their vessel. Along with a hand-picked band of your best marines, you hide inside some empty barrels in the hold. You do not have to wait long before the cry goes out from the look-out, warning of black sails on the horizon.\n\nGrappling hooks wrench the ships together and there is the desultory clash of steel. Your sailors put up a token resistance just to prevent the pirates getting suspicious, surrendering before anyone is killed. Listening from inside the barrel, you hear the tramp of feet on the deck above. Harsh commands are given and the barrels are loaded aboard the pirate ship. The slow rolling of the heavy merchantman gives way to the swift grace of the pirates\" warship.\n\nHours pass before you feel the ship jolt against the side of a dock. The pirates start to unload the barrels. You get ready to spring out on them, but then someone says, \"Let's broach this keg and have a party. We can unload the rest tomorrow.\"\n\nEven better. You wait until the noise of drunken carousing settles down into rhythmic snores, then you ease the top off your barrel and climb out. You emerge from the hold to find yourself in an underground lagoon covered by a vast stone dome. There are bronze braziers all along the shore of the lagoon, and the scene they illuminate is one of opulent luxury. The shore is covered with scattered gold, gems, ivory, pearls -- along with jars of oil and perfume, flasks of cool green wine and bolts of rich red cloth. The pirates lie asleep, limbs flung out like starfish in their wine-soaked contentment. Here you see a scar-faced villain clutching a necklace of dripping sapphires. Beside him lies a snoring red-faced ruffian hugging a blanket of lustrous silk.";

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

        if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
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

        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::SWORDPLAY, Skill::Type::WRESTLING}))
        {
            DAMAGE = -1;

            if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
            {
                PreText += "[SWORDPLAY] ";
            }

            if (Character::VERIFY_SKILL(player, Skill::Type::WRESTLING))
            {
                PreText += "[WRESTLING] ";
            }
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nYou still have breath in your body, you race off with the islanders in close pursuit.\n\nThe jetty comes in sight. Encouraged by the crew's yells, you ignore the stones and spears that are whistling past your heads. Leaping aboard, the captain gives the immediate order to cast off. The ship lurches out from the jetty and swirls on the river currents. You watch from the rail as the angry mob comes charging onto the jetty. Some career into the water in their haste, and now it is the turn of your crew to pelt them with missiles.\n\nAs he gets his breath back, Captain Ibrahim tells you that the islanders kept asking him about the nest of the rokh, the giant bird said to prey on elephants. \"I told them I wanted only to trade, but they were having none of it,\" he pants. \"They accused me of being after the rokh's diamond eggs.\"\n\n\"Its nest must be somewhere in these parts, then.\"\n\n\"They said it was somewhere to the west,\" he says with as much interest as if he were speaking about the shape of a bee's backside. \"But I think it\"s just so much poppycock.\"\n\nYou gained the codeword KISMET.";

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

        Text = "One of the ghoul brothers gives the signal and they go charging off down the path like a pair of stampeding elephants. You stand watching them in the moonlight. After fifty metres or so, one of them glances back and laughs, saying, \"Haw! You forgot to start at the signal. You don't have a chance of catching us now!\"\n\n\"You're right,\" you reply, \"I don't.\" And you shoot him through the heart.\n\nThe other ghoul skids to a halt, stares at his brother's corpse in shock, then glowers at you. He takes a step back along the trail, sees you nocking another arrow, and starts to back away.\n\nYou release the second arrow and watch it streak to find its mark. You give a sad shake of the head as you turn away. They were almost too easy. Now to deal with the vile monster that spawned them.\n\nShe looks up from tasting a ladle of stew as you kick the door in. Her slack blue-lipped mouth starts to frame a quizzical frown. The expression turns to a death grimace as your arrow splits her throat. Stepping over the body, you make a quick search of the hut, finding 15 dinars in a jar.\n\nYou also take a warm woollen cloak. You have no desire to spend the night here, and you will need something to keep warm while sheltering amid the rocks. The cloak is crawling with lice, but you hold it over the fire for a few minutes so that the smoke drives most of them out.";

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

        Text = "The four riders are garbed all in white, with silver filigree around the borders of their robes. Three look down with fierce eyes. The emotions of the fourth remain a mystery, for he wears a mask of carved ivory. All carry bristling lances. Knives and long swords hang at their belts.\n\nThe masked rider points to the fallen gazelle. \"This was our game, which we\"d pursued since before sunrise. You've stolen it.\" His voice sounds as sweet as the melody of a harp, as sweet as a fresh brook, as sweet as poisoned syrup.\n\nAbdullah becomes truculent. \"Who are you, to lay such accusations on us?\"\n\nThe masked stranger leans forward in his saddle. \"I am the Sultan of Nishapur.\"";

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

        Text = "The sailor speaks with rapture of the joys of seafaring. \"The salt spray has a scent more lovely than the spices of Ceylon,\" he says. \"And what jewel ever shone as bright as the setting sun, smouldering like a ruby above the languid gold of the ocean?\"\n\nAs you approach the docks, however, his mood becomes more practical. \"You'll first sail downriver to Basra,\" he says. \"From Basra on to the open sea of the Gulf. Once past the Straits of Hormuz, I'd counsel you to stay close to shore if you wish to avoid a hazardous adventure. Somewhere in the Indian Ocean lies the island of a malevolent dwarf. He has deep knowledge of dire sorcery. It's said that he does not welcome visitors, but nor does he hurry to see them leave again once they\"ve found his isle. His seven sentinels have as much mercy as sharks.\"\n\nYou nod, glancing away to hide your sceptical smile. \"I'm grateful for this advice. Are there other dangers of the deep I should watch out for?\"\n\nHe spreads his hands as if at an embarrassment of riches. \"The giant fish called the dendan, which swallows ships. The people of the Scarlet Isle, who are ruled by dead kings. The evil fire wizards whom the Prophet cast out from this land two centuries ago. And sundry ghosts, ifrits and cannibal pirates, of course...\"\n\nYou raise your eyebrows. \"Are you sure that going to sea is a good idea?\"\n\n\"Now I come to think,\" says the sailor, pulling thoughtfully at his beard, \"it is a perilous life at best. But consider the great rewards, my friend, if you should survive to reach one of those fabulous ports where silks and spices are as plentiful as the plums of the Caliph\"s garden.\"";

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

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::SWORDPLAY, Skill::Type::WRESTLING}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nWithout SWORDPLAY or WRESTLING skills you have no hope at all, and you go down fighting under a hail of blows.";
        }
        else
        {
            PreText += "\n\n";

            if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
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

        PreText = "A week later, the grille is hauled up and another prisoner is lowered into the oubliette. \"Here is the real Shadow!\" calls down a guard. \"Now you worthless wretches have got some distinguished company for a change.\"\n\nThe grille drops back into place with a clang. \"What about me?\" you shout up. \"If you\"ve got the real Shadow, you must know I'm innocent!\"\n\nThe guard's face reappears at the top. He has a broad smirk as he says, \"Innocent? You can\"t be innocent if you're in gaol, can you? So maybe you didn't steal the Sultan's ruby -- who cares? No doubt there's some other crime we can mark down to you.\"\n\n\"This is rank injustice!\" you call back, but he has gone.\n\nThe newcomer places a hand on your shoulder. \"I too am the victim of injustice, my friend, for I am not the Shadow. I thought you were. In fact, I got myself caught in order to meet you. My name is Azenomei.\" You turn and look at him: a handsome beardless young man with sparkling gaze. He has a small scar across the bridge of his nose.\n\n\"In that case, you\"re in for a big disappointment. And why are you smiling? Don't you know we'll probably stay here till we die?\"\n\nHis grin grows all the wider as he brings out a huge bunch of keys. \"Here I have the answer to nine hundred and ninety-nine locks. All we need is a way to reach the grille.\"";

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
        &story160, &story161, &story162, &story163, &story164, &story165, &story166, &story167, &story168, &story169};
}

#endif