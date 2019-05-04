/*****************************************************************************
* Model: mHoS.qm
* File:  ./mHoS.cpp
*
* This code has been generated by QM tool (see state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*****************************************************************************/
/*${.::mHoS.cpp} ...........................................................*/
#include "qhsm.h"
#include "mHoS.h"
#include "eventHandlers.h"
#include "glue.h"


#include <stdint.h>

//Q_DEFINE_THIS_FILE


/* protected: */
static QState MHoS_initial(MHoS * const me, QEvt const * const e);
static QState MHoS_global(MHoS * const me, QEvt const * const e);
static QState MHoS_dead(MHoS * const me, QEvt const * const e);
static QState MHoS_just_died(MHoS * const me, QEvt const * const e);
static QState MHoS_wait_reset(MHoS * const me, QEvt const * const e);
static QState MHoS_alive(MHoS * const me, QEvt const * const e);
static QState MHoS_NOT_IMMUNE(MHoS * const me, QEvt const * const e);
static QState MHoS_simple(MHoS * const me, QEvt const * const e);
static QState MHoS_mutant(MHoS * const me, QEvt const * const e);
static QState MHoS_immune(MHoS * const me, QEvt const * const e);

#ifdef DESKTOP
static QState MHoS_final(MHoS * const me, QEvt const * const e);
#endif /* def DESKTOP */



static MHoS mHoS; /* the only instance of the MHoS class */



/* global-scope definitions -----------------------------------------*/
QHsm * const the_mHoS = (QHsm *) &mHoS; /* the opaque pointer */

/*${SMs::MHoS_ctor} ........................................................*/
void MHoS_ctor(
    unsigned int HP,
    unsigned int MaxHP,
	unsigned int DefaultHP,
    unsigned int State)
{
    MHoS *me = &mHoS;
         me->CharHP = HP;
        me->MaxHP = MaxHP;
        me->DefaultHP = DefaultHP;
        me->ScaleStep = 255/MaxHP;
        me->DeathTime = 0;
        switch (State) {
            case SIMPLE: {
                me->StartState =
                (QStateHandler)&MHoS_simple;
                break;
            }
            case MUTANT: {
                me->StartState =
                (QStateHandler)&MHoS_mutant;
                break;
            }
            case DEAD: {
                me->StartState =
                (QStateHandler)&MHoS_wait_reset;
                break;

            }
            default:
                me->StartState =
                (QStateHandler)&MHoS_simple;
        }
     QHsm_ctor(&me->super, Q_STATE_CAST(&MHoS_initial));
}
/*${SMs::MHoS} .............................................................*/
/*${SMs::MHoS::SM} .........................................................*/
static QState MHoS_initial(MHoS * const me, QEvt const * const e) {
    /* ${SMs::MHoS::SM::initial} */
    return Q_TRAN(me->StartState);
    return Q_TRAN(&MHoS_simple);
}
/*${SMs::MHoS::SM::global} .................................................*/
static QState MHoS_global(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {

#ifdef DESKTOP
        /* ${SMs::MHoS::SM::global::TERMINATE} */
        case TERMINATE_SIG: {
            status_ = Q_TRAN(&MHoS_final);
            break;
        }
#endif /* def DESKTOP */

        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${SMs::MHoS::SM::global::dead} ...........................................*/
static QState MHoS_dead(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::global::dead::UPDATE_HP_SIG} */
		 case Q_ENTRY_SIG: {
			printf("entered dead\n");
            break;
        }
        case UPDATE_HP_SIG: {
			Flash(255, 0, 0, FLASH_MS);
            UpdateDefaultHP(me, ((mHoSQEvt*)e)->value);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::dead::PILL_HP_DOUBLE} */
        case PILL_HP_DOUBLE_SIG: {
            Double(me);
            status_ = Q_TRAN(&MHoS_simple);
            break;
        }
        /* ${SMs::MHoS::SM::global::dead::PILL_RESET} */
        case PILL_RESET_SIG: {
            Reset(me);
            status_ = Q_TRAN(&MHoS_simple);
            break;
        }
        default: {
            status_ = Q_SUPER(&MHoS_global);
            break;
        }
    }
    return status_;
}
/*${SMs::MHoS::SM::global::dead::just_died} ................................*/
static QState MHoS_just_died(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::global::dead::just_died} */
        case Q_ENTRY_SIG: {
			printf("Just died\n");
            SaveState(DEAD);
            UpdateHP(me, 0);
            Vibro(DEATH_TO_S*1000/3);
            Flash(255, 0, 0, DEATH_TO_S*1000);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::dead::just_died::TIME_TICK_1S} */
        case TIME_TICK_1S_SIG: {
            /* ${SMs::MHoS::SM::global::dead::just_died::TIME_TICK_1S::[DeathTime>DEATH_TO_S]} */
            if (me->DeathTime >  DEATH_TO_S) {
                status_ = Q_TRAN(&MHoS_wait_reset);
            }
            /* ${SMs::MHoS::SM::global::dead::just_died::TIME_TICK_1S::[else]} */
            else {
                me->DeathTime++;
                status_ = Q_HANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&MHoS_dead);
            break;
        }
    }
    return status_;
}
/*${SMs::MHoS::SM::global::dead::wait_reset} ...............................*/
static QState MHoS_wait_reset(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::global::dead::wait_reset} */
        case Q_ENTRY_SIG: {
            printf("Entered Wait Reset\n");
			me->DeathTime = 0;
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::dead::wait_reset::TIME_TICK_1S} */
        case TIME_TICK_1S_SIG: {
            Flash(255, 0, 0, FLASH_MS/5);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&MHoS_dead);
            break;
        }
    }
    return status_;
}
/*${SMs::MHoS::SM::global::alive} ..........................................*/
static QState MHoS_alive(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::global::alive::BUTTON_PRESSED} */
		case Q_ENTRY_SIG: {
			printf("entered alive\n");
            break;
        }
        case BUTTON_PRESSED_SIG: {
            ShowHP(me);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::PILL_HP_DOUBLE} */
        case PILL_HP_DOUBLE_SIG: {
            Flash(255, 0, 0, FLASH_MS);
            Double(me);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::PILL_HEAL} */
        case PILL_HEAL_SIG: {
            Flash(255, 165, 0, FLASH_MS);
            UpdateHP(me, me->MaxHP);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::UPDATE_HP_SIG} */
        case UPDATE_HP_SIG: {
			Flash(255, 0, 0, FLASH_MS);
            UpdateDefaultHP(me, ((mHoSQEvt*)e)->value);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::KILL_SIGNAL_RECEIVED} */
        case KILL_SIGNAL_RECEIVED_SIG: {
            status_ = Q_TRAN(&MHoS_just_died);
            break;
        }
        default: {
            status_ = Q_SUPER(&MHoS_global);
            break;
        }
    }
    return status_;
}
/*${SMs::MHoS::SM::global::alive::NOT_IMMUNE} ..............................*/
static QState MHoS_NOT_IMMUNE(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::DAMAGE_RECEIVED} */
        case Q_ENTRY_SIG: {
			printf("entered not immune\n");
            break;
        }
		case DAMAGE_RECEIVED_SIG: {
            /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::DAMAGE_RECEIVED::[me->CharHP<=((mHoSQEvt*)e)->dam~} */
            if (me->CharHP <= ((mHoSQEvt*)e)->value) {
                status_ = Q_TRAN(&MHoS_just_died);
            }
            /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::DAMAGE_RECEIVED::[else]} */
            else {
                me->CharHP -= ((mHoSQEvt*)e)->value;
                IndicateDamage(me);
                status_ = Q_HANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&MHoS_alive);
            break;
        }
    }
    return status_;
}
/*${SMs::MHoS::SM::global::alive::NOT_IMMUNE::simple} ......................*/
static QState MHoS_simple(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::simple} */
        case Q_ENTRY_SIG: {
            printf("Entered simple\n");
			SaveState(SIMPLE);
            Flash(0, 255, 0, FLASH_MS);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::simple::PILL_RESET} */
        case PILL_RESET_SIG: {
            Reset(me);
			Flash(0, 255, 0, FLASH_MS);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::simple::PILL_MUTANT} */
        case PILL_MUTANT_SIG: {
            status_ = Q_TRAN(&MHoS_mutant);
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::simple::PILL_IMMUNE} */
        case PILL_IMMUNE_SIG: {
            me->LastState = SIMPLE;
            status_ = Q_TRAN(&MHoS_immune);
            break;
        }
        default: {
            status_ = Q_SUPER(&MHoS_NOT_IMMUNE);
            break;
        }
    }
    return status_;
}
/*${SMs::MHoS::SM::global::alive::NOT_IMMUNE::mutant} ......................*/
static QState MHoS_mutant(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::mutant} */
        case Q_ENTRY_SIG: {
			printf("Entered mutant\n");
            SaveState(MUTANT);
            Flash(0, 0, 255, FLASH_MS);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::mutant::BUTTON_LONG_PRESSED} */
        case BUTTON_LONG_PRESSED_SIG: {
            SendKillingSignal();
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::mutant::PILL_SURGE} */
        case PILL_SURGE_SIG: {
            SendKillingSignal();
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::mutant::PILL_RESET} */
        case PILL_RESET_SIG: {
            Reset(me);
            status_ = Q_TRAN(&MHoS_simple);
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::NOT_IMMUNE::mutant::PILL_IMMUNE} */
        case PILL_IMMUNE_SIG: {
            me->LastState = MUTANT;
            status_ = Q_TRAN(&MHoS_immune);
            break;
        }
        default: {
            status_ = Q_SUPER(&MHoS_NOT_IMMUNE);
            break;
        }
    }
    return status_;
}
/*${SMs::MHoS::SM::global::alive::immune} ..................................*/
static QState MHoS_immune(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::global::alive::immune} */
        case Q_ENTRY_SIG: {
            printf("entered immune\n");
			ClearPill();
            Flash(255, 0, 255, FLASH_MS);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::immune::DAMAGE_RECEIVED} */
        case DAMAGE_RECEIVED_SIG: {
            Flash(0, 255, 0, FLASH_MS);
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::immune::PILL_REMOVED} */
        case PILL_REMOVED_SIG: {
            /* ${SMs::MHoS::SM::global::alive::immune::PILL_REMOVED::[me->LastState==MUTANT]} */
            if (me->LastState == MUTANT) {
                status_ = Q_TRAN(&MHoS_mutant);
            }
            /* ${SMs::MHoS::SM::global::alive::immune::PILL_REMOVED::[else]} */
            else {
                status_ = Q_TRAN(&MHoS_simple);
            }
            break;
        }
        /* ${SMs::MHoS::SM::global::alive::immune::TIME_TICK_1S} */
        case TIME_TICK_1S_SIG: {
			if (!(PillWasImmune())) {
                /* ${SMs::MHoS::SM::global::alive::immune::TIME_TICK_1S::[me->LastState==MUTANT]} */
                if (me->LastState == MUTANT) {
                    status_ = Q_TRAN(&MHoS_mutant);
                }
                /* ${SMs::MHoS::SM::global::alive::immune::TIME_TICK_1S::[else]} */
                else {
                   status_ = Q_TRAN(&MHoS_simple);
                }
                break;
			}
        }
        default: {
            status_ = Q_SUPER(&MHoS_alive);
            break;
        }
    }
    return status_;
}

#ifdef DESKTOP
/*${SMs::MHoS::SM::final} ..................................................*/
static QState MHoS_final(MHoS * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${SMs::MHoS::SM::final} */
        case Q_ENTRY_SIG: {
            printf("Bye! Bye!"); exit(0);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
#endif /* def DESKTOP */




/*tranlated from diagrams code*/

