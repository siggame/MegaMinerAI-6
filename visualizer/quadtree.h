#ifndef QUADTREE_H
#define QUADTREE_H
#include "structures.h"
#include "gameboardWidget.h"

struct Node
{

    Node * parent;
	Node * children[4];

    Bot * bot;

    Node()
    {
        parent = NULL;
        children[0] = NULL;
        children[1] = NULL;
        children[2] = NULL;
        children[3] = NULL;
        bot = NULL;
    }

    Node( Bot * input )
    {
        parent = NULL;
        children[0] = NULL;
        children[1] = NULL;
        children[2] = NULL;
        children[3] = NULL;
        bot = input;
    }

};


struct Quadtree
{
        Quadtree( Bot * root )
        {
            if ( root == NULL )
            {
            }
            else
            {
            m_root = new Node( root );
            }
        }

        Quadtree(  )
        {
            m_root = NULL;
        }

        virtual ~Quadtree()
        {
            clear();
        }

        void clear()
        {
            if (m_root != NULL )
                destroyBranch( m_root );

            m_root = NULL;
		}


		bool addNode( Bot * bot )
        {
            if ( !m_root ) // root case
            {
                m_root = new Node( bot );
				return true;
            }

            Node * temp = findNode( bot->partOf, m_root );




            if ( temp ) // all other cases
			{
				int botPos = 0;
				// Find bot position relative to the other bots
				int parentX = temp->bot->x, parentY = temp->bot->y,
					childX = bot->x, childY = bot->y;

				if ( ((parentX-childX) == 0) && ((parentY-childY) == 0)) //Up Left
				{
					botPos = 0;
				}
				else if ( ((parentX-childX) > 0) && ((parentY-childY) == 0)) //Up Right
				{
					botPos = 1;
				}
				else if ( ((parentX-childX) == 0) && ((parentY-childY) > 0)) //Down Left
				{
					botPos = 2;
				}
				else if ( ((parentX-childX) > 0) && ((parentY-childY) > 0)) //Down Right
				{
					botPos = 3;
				}



                if ( !temp->children[botPos] )
                {
                    temp->children[botPos] = new Node( bot );
                    linkToParent(temp,temp->children[botPos]);
					return true;
				}

			}

			return false;
        }

        void renderTree()
        {


        }

		void conformTypes()
		{
			conformTypes(m_root);
		}

        private:
        inline bool hasChildren(Node * node)
        {
            if (!node)
                return false;

            for (unsigned int i = 0; i < 4; i++)
            {
                if ( node->children[i] )
                    return true;
            }

            return false;
        }

		void conformTypes(Node * node)
		{
			if ( !node )
				return;

			if(hasChildren(node))
			{
				for (unsigned int i = 0; i < 4; i++)
				{
					conformTypes(node->children[i]);
				}

				int type = node->children[0]->bot->type;
				for (unsigned int i = 1; i < 4; i++)
				{
					if (type != node->children[i]->bot->type || type == 0)
					{
						type = 0;
					}
				}

				node->bot->type = type; //my only choice

			}
		}


        void destroyBranch(Node * node)
        {
			if (!node)
			{
				return;
			}

            for (unsigned int i = 0; i < 4; i++)
            {
                if ( hasChildren( node->children[i] ) )
                {
                    destroyBranch( node->children[i] );
                }
                else
                {
                    delete node->children[i];
                    node->children[i] = NULL;
                }
            }
        }

        inline void linkToParent( Node * parent, Node * child )
        {
            child ->parent = parent;
        }

        Node * findNode ( unsigned int botid , Node * node)
		{
            if ( !node )
                return NULL;

			Node * temp = node;

            if ( !temp->bot )
                return NULL;

            if ( temp->bot->id == botid )
                return temp;

            for (unsigned int i = 0; i < 4; i++)
            {
                Node * found = findNode( botid, temp->children[i] );
                if ( found )
                {
                    return found;
                }
            }

            return NULL;
        }

        Node * m_root;
};

#endif // QUADTREE_H
