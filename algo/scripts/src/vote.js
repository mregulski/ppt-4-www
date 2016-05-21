var voteMachine = (function(){
    // return {
    //     upvote: upvote,
    //     downvote: downvote
    // };

    var upBtn, downBtn, voteCount;

    window.addEventListener('load', init);



    function upvote() {
        var req = new XMLHttpRequest();
        req.addEventListener('load', updateVotes);
        req.responseType = 'json';
        req.open("POST", location.href + '/upvote', true);
        req.send();
        disableVoting();
    }

    function downvote() {
        var req = new XMLHttpRequest();
        req.addEventListener('load', updateVotes);
        req.responseType = 'json';
        req.open("POST", location.href + '/downvote');
        req.send();
        disableVoting();
    }

    function updateVotes(xhrEvent) {
        var votesCounter = document.getElementById("vote-count");
        if(xhrEvent == null)
            votesCounter.textContent = "0"
        else {
            votesCounter.textContent = xhrEvent.target.response.rating;
        }
    }

    function disableVoting() {
        var voteArea = document.getElementById('voting');
        voteArea.innerHTML = "<span>Twój głos został zapisany.</span>";
    }

    function init() {
        document.getElementById("btn-upvote")
            .addEventListener('click', upvote);
        document.getElementById("btn-downvote")
            .addEventListener('click', downvote);
        var initReq = new XMLHttpRequest();
        initReq.addEventListener('load', updateVotes);
        initReq.responseType = 'json';
        initReq.open('GET', location.href + '/rating');
        initReq.send();
    }
})();
