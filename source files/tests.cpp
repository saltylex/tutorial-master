#include <iostream>
#include <cassert>
#include "../header files/tutorial.h"
#include "../header files/repo.h"
#include "../header files/dynamicArray.h"
#include "../header files/service.h"

void test_tutorial(){
    std::string tutorial_copy;
    Tutorial t = Tutorial();
    t = Tutorial("title", "presenter", Duration{1,20}, 3, "https://www.youtube.com/watch?v=jqONINYF17M");
    tutorial_copy = t.to_string();
    assert(t.get_duration().minutes == 1);
    assert(t.get_duration().seconds == 20);
    assert(t.get_likes() == 3);
    assert(t.get_title() == "title");
    assert(t.get_presenter() == "presenter");
    assert(t.get_link() == "https://www.youtube.com/watch?v=jqONINYF17M");
    t.update("new","new_p",Duration{1,2},3,"https://www.youtube.com/watch?v=jqONINYF17M");
    assert(t.get_title() == "new");
    std::string tut = t.to_string();
    assert(tut == "new by new_p | 1:02 | Likes:3\nhttps://www.youtube.com/watch?v=jqONINYF17M");
    std::cout<<"Tutorial tested.\n";
}

void test_repo(){
    Repo test_repo;
    Tutorial t = Tutorial("title", "presenter", Duration{1,20}, 3, "https://www.youtube.com/watch?v=jqONINYF17M");
    // remove, get_size, get_index, get_at
    assert(test_repo.find("lol") == false);
    test_repo.add(t);
    assert(test_repo.find("https://www.youtube.com/watch?v=jqONINYF17M") == true);
    assert(test_repo.get_size()==1);
    assert(test_repo.get_index("https://www.youtube.com/watch?v=jqONINYF17M")==0);
    assert(test_repo.get_at(0)==t);
    test_repo.remove(t);
    assert(test_repo.find("https://www.youtube.com/watch?v=jqONINYF17M") == false);
    assert(test_repo.get_index("https://www.youtube.com/watch?v=jqONINYF17M")==-1);
    std::cout<<"Repo tested.\n";


}

void test_service(){
    Repo repo, watch, queueue;
    Service serv = Service(repo, watch, queueue);
    serv.add_to_repo("title","presenter",Duration{1,1}, 32,"https://www.youtube.com/watch?v=jqONINYF17M");
    assert(serv.get_size() == 1);
    assert(serv.get_repo().get_at(0)==Tutorial("title","presenter",Duration{1,1},32,"https://www.youtube.com/watch?v=jqONINYF17M"));
    assert(serv.get_watch_list().get_size()==0);
    assert(serv.get_queue().get_size()==0);
    assert(serv.search_in_repo("pres").get_size()==1);
    serv.update_in_repo("new_title","new_presenter",Duration{2,2},33,"https://www.youtube.com/watch?v=jqONINYF17M","new_link");
    assert(serv.get_repo().get_at(0).get_title()=="new_title");
    serv.remove_from_repo("new_link");
    assert(serv.get_repo().get_size()==0);
    Tutorial tut = Tutorial("title","presenter",Duration{1,1},32,"https://www.youtube.com/watch?v=jqONINYF17M");
    serv.add_to_watch_list(tut);
    assert(serv.get_watch_list().get_size()==1);
    serv.remove_from_watch_list(0);
    assert(serv.get_watch_list().get_size()==0);
    std::cout<<"Service tested.\n";
}

void test_array(){
        DynamicArray<int> arr;
        assert(arr.get_size() == 0);
        arr.add(1);
        arr.add(2);
        assert(arr[0] == 1);
        assert(arr[1] == 2);
        DynamicArray<int> arr2 = DynamicArray<int>(arr);
        assert(arr2[0] == 1);
        assert(arr2[1] == 2);

        arr.clear();
        assert(arr.get_size() == 0);

        arr = arr2;
        assert(arr[0] == 1);
        assert(arr[1] == 2);
        assert(arr.get_size() == 2);
        arr.remove(0);
        assert(arr[0] == 2);
        assert(arr.get_size() == 1);
        arr = arr;
        assert(arr[0] == 2);
        assert(arr.get_size() == 1);
        std::cout<<"Array tested.\n";
    }


void test_everything() {
    test_tutorial();
    test_repo();
    test_service();
    test_array();
    std::cout<<"All tests passed!\n\n";
}