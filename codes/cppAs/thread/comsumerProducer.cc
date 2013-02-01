void* producer(void *arg)
{
    while(true)
    {   pthread_mutex_lock(&_dealmutex);
        _nCurrProductor ++;
        cout<<"I Produced One."<<endl;
        pthread_mutex_unlock(&_dealmutex);
    }
}
void* customer(void *arg)
{
    while(true)
    {
        pthread_mutex_lock(&_dealmutex);
        if(_nCurrProductor > 0)
        {
            _nCurrProductor --;
            cout<<"Haha, I Ate One."<<endl;
        }
        else
        {
            cout<<"Baby, Come On. I am hungry."<<endl;
        }
        pthread_mutex_unlock(&_dealmutex);
    }
}
int main(int argc, char** argv)
{
    cout<<"Let's Go!!!"<<endl;
    pthread_mutex_init(&_dealmutex, NULL);
    pthread_t pt1;
    pthread_t pt2;
    int divt2 = pthread_create(&pt2, NULL, customer, NULL);
    int divt1 = pthread_create(&pt1, NULL, producer, NULL);
    if(divt1 != 0 || divt2 != 0)
    {
        cout<<"Thread Create Failed."<<endl;
        exit(1);
    }
    while(true)
    {
    }
    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);
    cout<<"Game Over!"<<endl;
    return 0;
}

