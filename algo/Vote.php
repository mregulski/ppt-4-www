<?php
    function saveVote($page, $vote) {
        //votes.page += vote
        $json = file_get_contents('votes.json');
        $data = json_decode($json);
        foreach ($data->pages as $key => $pageVoteData) {
            // echo "current: ";
            // var_dump($pageVoteData);
            // echo "<br>";
            if($pageVoteData->name===$page) {
                $pageVoteData->rating += $vote;
                $updatedRating = $data->pages[$key];
            }
        }
        $response = json_encode($updatedRating);
        // echo "response:".$response."<br>";
        $json = json_encode($data);
        fwrite(fopen('votes.json', 'w'), $json);
        header('Content-Type: application/json; charset=utf-8');
        echo $response;
        exit();
    }

    function getVotes($page) {
        $json = file_get_contents('votes.json');
        $data = json_decode($json);
        foreach ($data->pages as $key => $pageVoteData) {
            if($pageVoteData->name===$page) {
                $pageRating = $data->pages[$key];
                break;
            }
        }

        $response = json_encode($pageRating);
        header('Content-Type: application/json; charset=utf-8');
        echo $response;
        exit();
    }

    $action = $_REQUEST['action'];
    $page = $_REQUEST['page'];
    if ($_SERVER['REQUEST_METHOD'] === 'GET' && $action === "") {
       getVotes($page);
    } else if($_SERVER['REQUEST_METHOD'] === 'POST') {

        if($action === 'upvote') {
            saveVote($page, 1);
        }
        else if($action === 'downvote') {
            saveVote($page, -1);
        }
    }
    else {
        http_response_code('400');
    }

?>
