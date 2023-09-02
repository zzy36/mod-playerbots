/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CasterDruidStrategy.h"
#include "AiObjectContext.h"
#include "FeralDruidStrategy.h"

class CasterDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        CasterDruidStrategyActionNodeFactory()
        {
            creators["faerie fire"] = &faerie_fire;
            creators["hibernate"] = &hibernate;
            creators["entangling roots"] = &entangling_roots;
            creators["entangling roots on cc"] = &entangling_roots_on_cc;
            creators["wrath"] = &wrath;
            creators["starfall"] = &starfall;
            creators["insect swarm"] = &insect_swarm;
            creators["moonfire"] = &moonfire;
            creators["starfire"] = &starfire;
        }

    private:
        static ActionNode* faerie_fire([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("faerie fire",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* hibernate([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("hibernate",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ NextAction::array(0, new NextAction("entangling roots"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* entangling_roots([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("entangling roots",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* entangling_roots_on_cc([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("entangling roots on cc",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* wrath([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("wrath",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* starfall([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("starfall",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* insect_swarm([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("insect swarm",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* moonfire([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("moonfire",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* starfire([[maybe_unused]] PlayerbotAI* botAI)
        {
            return new ActionNode ("starfire",
                /*P*/ NextAction::array(0, new NextAction("moonkin form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }
};

CasterDruidStrategy::CasterDruidStrategy(PlayerbotAI* botAI) : GenericDruidStrategy(botAI)
{
    actionNodeFactories.Add(new CasterDruidStrategyActionNodeFactory());
    actionNodeFactories.Add(new ShapeshiftDruidStrategyActionNodeFactory());
}

NextAction** CasterDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, 
        new NextAction("starfall", ACTION_NORMAL + 2),
        new NextAction("wrath", ACTION_NORMAL + 1), 
        // new NextAction("starfire", ACTION_NORMAL), 
        nullptr);
}

void CasterDruidStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("enemy out of spell", NextAction::array(0, new NextAction("reach spell", ACTION_MOVE), nullptr)));
    triggers.push_back(new TriggerNode("insect swarm", NextAction::array(0, new NextAction("insect swarm", ACTION_NORMAL + 5), nullptr)));
	triggers.push_back(new TriggerNode("moonfire", NextAction::array(0, new NextAction("moonfire", ACTION_NORMAL + 4), nullptr)));
    triggers.push_back(new TriggerNode("eclipse (solar)", NextAction::array(0, new NextAction("wrath", ACTION_NORMAL + 6), nullptr)));
    triggers.push_back(new TriggerNode("eclipse (lunar) cooldown", NextAction::array(0, new NextAction("starfire", ACTION_NORMAL + 2), nullptr)));
    triggers.push_back(new TriggerNode("eclipse (lunar)", NextAction::array(0, new NextAction("starfire", ACTION_NORMAL + 6), nullptr)));
    triggers.push_back(new TriggerNode("eclipse (solar) cooldown", NextAction::array(0, new NextAction("wrath", ACTION_NORMAL + 2), nullptr)));
    triggers.push_back(new TriggerNode("moonfire", NextAction::array(0, new NextAction("moonfire", ACTION_NORMAL + 4), nullptr)));
	triggers.push_back(new TriggerNode("medium mana", NextAction::array(0, new NextAction("innervate", ACTION_HIGH + 9), NULL)));
    triggers.push_back(new TriggerNode("enemy too close for spell", NextAction::array(0, new NextAction("flee", ACTION_HIGH), nullptr)));
    triggers.push_back(new TriggerNode(
        "party member remove curse",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL + 7), NULL)));
}

void CasterDruidAoeStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
	triggers.push_back(new TriggerNode("high aoe", NextAction::array(0, new NextAction("hurricane", ACTION_HIGH + 1), nullptr)));
    triggers.push_back(new TriggerNode(
		"light aoe",
        NextAction::array(0,
            new NextAction("starfall", ACTION_NORMAL + 5),
		    new NextAction("insect swarm on attacker", ACTION_NORMAL + 3), 
            new NextAction("moonfire on attacker", ACTION_NORMAL + 3),
            NULL)));
}

void CasterDruidDebuffStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("faerie fire", NextAction::array(0, new NextAction("faerie fire", ACTION_HIGH), nullptr)));
}
