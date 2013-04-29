double ComputeEntropy(vector <vector <string> > remain_state, string attribute, 
string value,bool ifparent)
{   
    vector<int> count (2,0);   
    unsigned int i,j;   
    bool done_flag = false;//???   
    for(j = 1; j < MAXLEN; j++){   
        if(done_flag) break;   
        if(!attribute_row[j].compare(attribute)){   
            for(i = 1; i < remain_state.size(); i++){   
                if((!ifparent&&!remain_state[i][j].compare(value)) || ifparent){//ifparent????????   
                    if(!remain_state[i][MAXLEN - 1].compare(yes)){   
                        count[0]++;   
                    }   
                    else count[1]++;   
                }   
            }   
            done_flag = true;   
        }   
    }   
    if(count[0] == 0 || count[1] == 0 ) return 0;//???????????   
    //????? ??[+count[0],-count[1]],log2???????????????   
    double sum = count[0] + count[1];   
    double entropy = -count[0]/sum*log(count[0]/sum)/log(2.0) - count[1]/sum*log(count[1]/sum)/log(2.0);   
    return entropy;   
}   

Node * BulidDecisionTreeDFS(Node * p, vector <vector <string> > remain_state, vector <string> remain_attribute){   
    //if(remain_state.size() > 0){   
        //printv(remain_state);   
    //}   
    if (p == NULL)   
        p = new Node();   
    //??????????   
    if (AllTheSameLabel(remain_state, yes)){   
        p->attribute = yes;   
        return p;   
    }   
    if (AllTheSameLabel(remain_state, no)){   
        p->attribute = no;   
        return p;   
    }   
    if(remain_attribute.size() == 0){//????????????,?????   
        string label = MostCommonLabel(remain_state);   
        p->attribute = label;   
        return p;   
    }   
   
    double max_gain = 0, temp_gain;   
    vector <string>::iterator max_it;   
    vector <string>::iterator it1;   
    for(it1 = remain_attribute.begin(); it1 < remain_attribute.end(); it1++){   
        temp_gain = ComputeGain(remain_state, (*it1));   
        if(temp_gain > max_gain) {   
            max_gain = temp_gain;   
            max_it = it1;   
        }   
    }   
    //????max_it????????????,?????????   
    vector <string> new_attribute;   
    vector <vector <string> > new_state;   
    for(vector <string>::iterator it2 = remain_attribute.begin(); it2 < remain_attribute.end(); it2++){   
        if((*it2).compare(*max_it)) new_attribute.push_back(*it2);   
    }   
    //?????????,????   
    p->attribute = *max_it;   
    vector <string> values = map_attribute_values[*max_it];   
    int attribue_num = FindAttriNumByName(*max_it);   
    new_state.push_back(attribute_row);   
    for(vector <string>::iterator it3 = values.begin(); it3 < values.end(); it3++){   
        for(unsigned int i = 1; i < remain_state.size(); i++){   
            if(!remain_state[i][attribue_num].compare(*it3)){   
                new_state.push_back(remain_state[i]);   
            }   
        }   
        Node * new_node = new Node();   
        new_node->arrived_value = *it3;   
        if(new_state.size() == 0){//?????????????,???new_node?????   
            new_node->attribute = MostCommonLabel(remain_state);   
        }   
        else    
            BulidDecisionTreeDFS(new_node, new_state, new_attribute);   
        //?????????????1 ????????????? 2??new_state??   
        p->childs.push_back(new_node);   
        new_state.erase(new_state.begin()+1,new_state.end());//?????new_state??????????,???????????   
    }   
    return p;   
}    

