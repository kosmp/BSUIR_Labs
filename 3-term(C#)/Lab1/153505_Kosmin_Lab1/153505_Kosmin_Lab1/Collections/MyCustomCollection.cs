using _153505_Kosmin_Lab1.Interfaces;
using System.Collections;

namespace _153505_Kosmin_Lab1.Collections
{
    public class Node<P>
    {
        public P? Value { get; set; }
        public Node<P>? Next { get; set; }  
        public Node<P>? Prev { get; set; }

        public Node(P value)
        {
            Value = value;
            Next = null;
            Prev = null;
        }
    }

    public class MyCustomCollection<T> : IEnumerable<T>, ICustomCollection<T>
    {
        private Node<T>? head;
        private Node<T>? tail;
        private Node<T>? cursor;
        private int size = 0;

        public T? this[int index]
        {
            get
            {
                Node<T>? currNode = head;
                for (int i = 0; i <= index; i++)
                {
                    if (currNode != null)
                    {
                        if (i == index) return currNode.Value;
                        currNode = currNode.Next;
                    }
                }
                return default;
            }
            set 
            {
                Node<T>? currNode = head;
                for (int i = 0; i <= index; i++)
                {
                    if (currNode != null)
                    {
                        if (i == index) currNode.Value = value;
                        currNode = currNode.Next;
                    }
                }
            }
        }

        public void Reset()
        {
            cursor = head;
        }

        public void Next()
        {
            if (cursor != null)
            {
                cursor = cursor.Next;
            }
        }

        public T? Current()
        {
            if (cursor != null)
            {
                return cursor.Value;
            }
            return default;
        }

        public int Count
        {
            get
            {
                return size;
            }
        }

        public void Add(T item)
        {
            if (Count == 0)
            {
                head = tail = new Node<T>(item);
            }
            else
            {
                Node<T>? tempTail = tail;
                tail = new Node<T>(item);
                if (tempTail == null) return;
                tempTail.Next = tail;
                tail.Prev = tempTail;
            }
            size++;
        }

        public void Remove(T item)
        {
            if (item == null) return;

            Node<T>? tempNode = head;
            for (int i = 0; i < size; i++)
            {
                if (tempNode != null)
                {
                    if (item.Equals(tempNode.Value))
                    {
                        if (tempNode.Next != null)
                        {
                            if (tempNode.Prev != null)
                            {
                                Node<T> nextNode = tempNode.Next;
                                nextNode.Prev = tempNode.Prev;
                                tempNode.Prev.Next = nextNode;
                            }
                            else
                            {
                                head = tempNode.Next;
                                head.Prev = null;
                            }
                            size--;
                        }
                        else
                        {
                            if (tempNode.Prev == null)
                            {
                                tail = head = null;
                            }
                            else
                            {
                                tail = tempNode.Prev;
                                tail.Next = null;
                            }
                            size--;
                        }
                    }
                    tempNode = tempNode.Next;
                }
            }
        }

        public T? RemoveCurrent()
        {
            if (size != 0 && cursor != null)
            {
                if (cursor.Next != null)
                {
                    if (cursor.Prev != null)
                    {
                        Node<T> nextNode = cursor.Next;
                        nextNode.Prev = cursor.Prev;
                        cursor.Prev.Next = nextNode;
                        cursor = nextNode;
                    }
                    else
                    {
                        head = cursor.Next;
                        head.Prev = null;
                        cursor = head;
                    }
                    size--;
                }
                else
                {
                    if (cursor.Prev == null)
                    {
                        tail = head = null;
                    }
                    else
                    {
                        tail = cursor.Prev;
                        tail.Next = null;
                    }
                    cursor = null; // no next node, so cursor = null
                    size--;
                }
            }
            if (cursor == null)
                return default;
            else
                return cursor.Value;
        }

        IEnumerator<T> IEnumerable<T>.GetEnumerator()
        {
            Node<T> current = head;
            while (current != null)
            {
                yield return current.Value;
                current = current.Next;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)this).GetEnumerator();
        }
    }
}
