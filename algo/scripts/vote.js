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
    }

    function downvote() {
        var req = new XMLHttpRequest();
        req.addEventListener('load', updateVotes);
        req.responseType = 'json';
        req.open("POST", location.href + '/downvote');
        req.send();
    }

    function updateVotes(xhrEvent) {
        document
            .getElementById("vote-count")
            .textContent = xhrEvent.target.response.rating;
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
