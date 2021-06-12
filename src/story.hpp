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
        SELL
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
        TRADE
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

        Text = "\"Perhaps this tale is true, perhaps not. Only God knows all,\" begins the old storyteller. \"It concerns a young prince who, while travelling in the wilderness, came to a hut of mud bricks. Drawing water from the well, he was taken unawares by two strong brothers who came upon him from behind. They carried him to their mother, an aged crone with a face as withered as a rotten gourd. Her teeth were like broken pebbles, her eyes filmy with rheum. And the prince knew from their white skin that these were not mortals, but a family of ghouls. Then he feared for his life, but even in his terror his wits did not entirely desert him. 'Am I to die without a chance to save myself?' he asked as they stoked the fire.\n\n\"The ancient she-ghoul leered as she sprinkled the seasoning. 'What chance would you have?' she asked. 'In any contest, my sons are superior to a mortal man.'\n\n'I have no skill with weapons,' replied the prince. 'But in my own land I am famous as an athlete. Why not set me free with a head start? Then, if your sons are fleet of foot, they can try to hunt me down. They will return with good appetites, and no scraps at the table will go to waste.'\"\n\nThe captain has come over and heard part of this tale. Butting in, he turns to you and says, \"Why waste your time on this foolishness? This is a tale for the witless. Does this old man think us as credulous as any village peasant?\"";

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

        Text = "There is indeed a tingle of recuperative energy as you taste the delicious crisp FRUIT on your tongue.\n\nThe merchant was as good as his word -- almost as great a miracle in itself as the magic healing. You gaze longingly at his stock of apples. These are a prize worth more than gold to a daring adventurer like yourself.\n\n\"You'd like to buy more?\" he asks.\n\nYou try not to appear too eager. \"At five dinars each? Recovery from one serious sword-blow would require enough fruit to pauper me!\"\n\n\"Perhaps we can barter,\" he suggests.";

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

        Text = "Now that the danger is over, you find you are trembling in shock. You sit on the end of Ayisha\"s couch while you recover. \"Where did you learn sorcery?\"\n\n\"My old nurse taught me,\" she replies, smiling. \"Alas, she never told me any spell to undo these enchanted chains.\"\n\n\"There must be a key.\"\n\nAyisha nods. \"There is. It is in the nest of the giant bird known as the rokh. If you\"d agree to try and get it, I could send you there with another spell I know.\" She pauses and adds hesitantly, \"It would be dangerous, of course.\"";

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

        Text = "The Isle of Palms is a wild windswept place off the southern tip of India. Putting into a cove, you wade ashore. \"We'll wait here,\" says Umar, the sailor in charge of the boat. \"If you\"re not back by daybreak tomorrow then, er, well...\"\n\nYou nod. \"I'll be back.\"\n\nThe interior of the island consists of grassy slopes surrounding a high pinnacle of rock whose peak is hidden in the clouds. Seeing sheep grazing in a valley nearby, you saunter over and find a shepherd who tells you, \"Yes, the rokh's nest is atop that pinnacle. Have you come to slay it?\"\n\nYou give an astonished laugh. \"Hardly. From what I\"ve heard, that would take an army.\"\n\nThe shepherd shrugs. \"Pity. It\"s forever stealing my sheep -- swoops down, grabs one, then carries it back to its nest.\"\n\n\"Maybe you should go and live elsewhere.\"\n\n\"Preposterous! The grass here is the richest to be found in all the world. See how plump my sheep are, the quality of their wool.\"\n\nThanking the shepherd for his help, you head towards the pinnacle.";

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

        Character::LOSE_ALL(player);

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

        Text = "In his hurry to get away, Yussuf stumbles into you and the taper falls to the floor. You try to shove him away so that you can retrieve it, but it gets trodden underfoot. Darkness descends like a raven\"s wing.\n\nOut of the dreadful heart-stopping silence, the only sound to be heard is the ragged rasp of Yussuf\"s sobbing. \"Merciful God, spare your unworthy servant,\" he pleads. \"Never will I thieve nor cheat at dice again. No drop of wine will touch my lips--\"\n\n\"Yussuf, listen!\" You reach out a hand and shake him until he gathers his wits.\n\n\"There's nothing ...\" he says in a voice of budding hope. \"What happened to the monsters?\"\n\nStepping forward to look for the taper, you tread on something which squelches under your heel. As Yussuf picks up and relights the taper, you see that you have crushed a swarm of beetles.\n\n\"There are the monsters.\"\n\nYussuf gasps in wonder. \"Tiny insects! But the things we saw were huge.\"\n\n\"Magical mirages. The terrors of our own minds were almost turned against us.\" You peer into the gloom ahead. \"We must be on our guard, my friend. This is a place of dark sorcery.\"";

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

void InitializeStories()
{
    Stories = {
        &prologue,
        &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009, &story010,
        &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019, &story020,
        &story021, &story022, &story023, &story024, &story025, &story026, &story027, &story028, &story029, &story030};
}

#endif