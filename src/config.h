#ifndef CONFIG
#define CONFIG

#include "main.h"
#include <vector>

const uint8_t LEFT_MOTOR_BACK_PORT = 15;
const uint8_t RIGHT_MOTOR_BACK_PORT = 14;
const uint8_t LEFT_MOTOR_FRONT_PORT = 13;
const uint8_t RIGHT_MOTOR_FRONT_PORT = 12;
const uint8_t CENTER_MOTOR_PORT = 11;

const uint8_t INTAKE_MOTOR_PORT = 10;

const uint8_t MOGO_MOTOR_PORT = 9;
const uint8_t MOGO_RELEASE_MOTOR_PORT = 8;


const float PI = 3.1415962;
const uint8_t WHEEL_CIRCUMFERENCE = 4 * PI; // inches
const uint8_t TILE_LENGTH = 24; // inches

extern const pros::controller_analog_e_t& FORWARD_BACK_AXIS;// = ANALOG_LEFT_Y;
extern const pros::controller_analog_e_t& TURN_AXIS;// = ANALOG_RIGHT_X;
extern const pros::controller_analog_e_t& STRAFE_AXIS;// = ANALOG_LEFT_X;

extern const pros::controller_digital_e_t& MOGO_OUT;// = DIGITAL_L2;
extern const pros::controller_digital_e_t& MOGO_IN;// = DIGITAL_L1;

extern const pros::controller_digital_e_t& MOGO_RELEASE;

extern const pros::controller_digital_e_t& INTAKE_IN;
extern const pros::controller_digital_e_t& INTAKE_OUT;

// auton creation keybinds
namespace auton
{
	const auto a_FORWARD = pros::E_CONTROLLER_DIGITAL_UP;
	const auto a_BACKWARD = pros::E_CONTROLLER_DIGITAL_DOWN;
	const auto a_STRAFE_RIGHT = pros::E_CONTROLLER_DIGITAL_RIGHT;
	const auto a_STRAFE_LEFT = pros::E_CONTROLLER_DIGITAL_LEFT;

	const auto a_INTAKE_IN = pros::E_CONTROLLER_DIGITAL_A;

	//const auto a_TURN = pros::E_CONTROLLER_DIGITAL_

	const auto a_MOGO_OUT = pros::E_CONTROLLER_DIGITAL_L2;
	const auto a_MOGO_IN = pros::E_CONTROLLER_DIGITAL_L1;

	const auto a_MOGO_RELEASE = pros::E_CONTROLLER_DIGITAL_X;

	const auto a_LESSEN_LAST = pros::E_CONTROLLER_DIGITAL_R1;
	const auto a_BOOST_LAST = pros::E_CONTROLLER_DIGITAL_R2;

	const auto a_BREAK = pros::E_CONTROLLER_DIGITAL_Y;

	const auto a_REMOVE_LAST = pros::E_CONTROLLER_DIGITAL_B;
}

enum AutonActionType
{
  FORWARD_BACKWARD, TURN, STRAFE, INTAKE_SPIN, MOGO_IN_OUT, MOGO_RELEASE
};

class AutonAction
{
private:
  AutonActionType type;
  float mag;
public:
  AutonAction(AutonActionType type, uint16_t mag) { this->type = type; this->mag = mag; }
  AutonActionType getType() { return type; }
  void change(int change) { mag += change; }
	float getMagnitude() { return mag; }
};

/*
TODO store autonActions in an deque

import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item>
{
    private Node<Item> head;
    private int size;

    // construct an empty deque
    public Deque()
    {
        size = 0;
    }

    // is the deque empty?
    public boolean isEmpty()
    {
        return size == 0;
    }

    // return the number of items on the deque
    public int size()
    {
        return size;
    }

    // add the item to the front
    public void addFirst(Item item)
    {
        if (item == null)
            throw new IllegalArgumentException("Tried to add null element to Deque");

        if (isEmpty())
        {
            head = new Node<Item>(item);
            head.setLast(head);
        }
        else
        {
            Node<Item> oldHead = head;
            head = new Node<Item>(item);
            head.setNext(oldHead);
            head.setLast(oldHead.getLast());
            oldHead.setLast(head);
        }
        size++;
    }

    // add the item to the back
    public void addLast(Item item)
    {
        if (isEmpty())
            addFirst(item);
        else
        {
            if (item == null)
                throw new IllegalArgumentException("Tried to add null element to Deque");

            Node<Item> oldLast = head.getLast();
            Node<Item> newLast = new Node<Item>(item);
            oldLast.setNext(newLast);
            newLast.setLast(oldLast);
            head.setLast(newLast);
            size++;
        }
    }

    // remove and return the item from the front
    public Item removeFirst()
    {
        if (size == 0)
            throw new NoSuchElementException("Tried to remove first element from empty Deque");
        else if (size > 1)
            head.getNext().setLast(head.getLast());

        Item headValue = head.getValue();
        head = head.getNext();
        size--;
        return headValue;
    }

    // remove and return the item from the back
    public Item removeLast()
    {
        if (size == 0)
            throw new NoSuchElementException("Tried to remove last element from empty Deque");

        Node<Item> oldLast = head.getLast();
        head.setLast(oldLast.getLast());
        head.getLast().setNext(null);
        size--;
        return oldLast.getValue();
    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator()
    {
        return new DequeIterator();
    }

    private class DequeIterator implements Iterator<Item>
    {
        private Node<Item> currentNode = head;

        private DequeIterator()
        {

        }

        public boolean hasNext()
        {
            return currentNode != null;
        }

        public Item next()
        {
            try
            {
                Item item = currentNode.getValue();
                currentNode = currentNode.getNext();
                return item;
            }
            catch (NullPointerException e)
            {
                throw new NoSuchElementException("Called next() on Deque iterator when there are no more elements");
            }
        }

        public void remove()
        {
            throw new UnsupportedOperationException("remove() is an unsupported operation");
        }
    }

    private class Node<Item>
    {
        private Item value;

        private Node<Item> next;
        private Node<Item> last;

        public Node(Item value)
        {
            this.value = value;
        }

        public void setNext(Node<Item> next)
        {
            this.next = next;
        }

        public void setLast(Node<Item> last)
        {
            this.last = last;
        }

        public Item getValue()
        {
            return value;
        }

        public Node<Item> getNext()
        {
            return next;
        }

        public Node<Item> getLast()
        {
            return last;
        }
    }

    // unit testing (required)
    // call directly every public constructor and method to help verify that they work as prescribed (e.g., by printing results to standard output).
    public static void main(String[] args)
    {
        Deque<String> deque = new Deque<>();
        System.out.println("isEmpty(): " + deque.isEmpty());
        deque.addFirst("Hello");
        deque.addLast("World");
        System.out.println("size(): " + deque.size());
        deque.removeFirst();
        System.out.println("size(): " + deque.size());
        deque.removeLast();
        System.out.println("size(): " + deque.size());

        for (int i = 0; i < 10; i++)
            if (i % 2 == 0)
                deque.addFirst("" + i);
            else
                deque.addLast("" + i);

        Iterator<String> iter = deque.iterator();
        while (iter.hasNext())
        {
            System.out.print(iter.next() + " ");
        }
        System.out.println();
    }
}
*/

extern std::vector<AutonAction*>* autonActions;
extern pros::Controller* controller;

extern pros::Motor* left_mtr_back;//(LEFT_MOTOR_BACK_PORT);
extern pros::Motor* right_mtr_back;//(RIGHT_MOTOR_BACK_PORT);
extern pros::Motor* left_mtr_front;//(LEFT_MOTOR_FRONT_PORT);
extern pros::Motor* right_mtr_front;//(RIGHT_MOTOR_FRONT_PORT);
extern pros::Motor* center_mtr;

extern pros::Motor* intake_mtr;
extern pros::Motor* mogo_mtr;
extern pros::Motor* mogo_release_mtr;

#endif
