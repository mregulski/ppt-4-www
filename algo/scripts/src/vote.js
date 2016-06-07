var voteMachine = (function(){


    var upBtn, downBtn, voteCount;

    var vote = 0;
    window.addEventListener('load', init);
    return {
        vote: function() {return vote;}
    };
    
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
        req.open("POST", location.href + '/downvote', true);
        req.send();
    }

    function updateVotes(xhrEvent) {
        var votesCounter = document.querySelector('#feedback .vote-count');
        if(xhrEvent == null)
            votesCounter.textContent = "?"
        else {
            votesCounter.textContent = xhrEvent.target.response.rating;
        }
    }

    function init() {
        upBtn = document.querySelector("#feedback .upvote");
        downBtn = document.querySelector("#feedback .downvote");
        upBtn.onclick = upClick();
        downBtn.onclick = downClick();
        getVotes();
    }

    function getVotes() {
        var initReq = new XMLHttpRequest();
        initReq.addEventListener('load', updateVotes);
        initReq.responseType = 'json';
        initReq.open('GET', location.href + '/rating');
        initReq.send();
    }

    function upClick() {
        if(vote == 1) {
            return function() {
                vote = 0;
                downvote();
                upBtn.onclick = upClick();
                downBtn.onclick = downClick();
                upBtn.classList.remove('clicked');
            }
        }
        if(vote == 0) {
            return function() {
                vote = 1;
                upvote();
                upBtn.onclick = upClick();
                downBtn.onclick = downClick();
                upBtn.classList.add('clicked');
            }

        }
        if(vote == -1) {
            return function() {
                vote = 1;
                upvote();
                upvote();
                upBtn.onclick = upClick();
                downBtn.onclick = downClick();
                upBtn.classList.add('clicked');
                downBtn.classList.remove('clicked');
            }
        }
    }

    function downClick() {
        if(vote == 1) {
            return function() {
                vote = -1;
                downvote();
                downvote();
                downBtn.onclick = downClick();
                upBtn.onclick = upClick();
                upBtn.classList.remove('clicked');
                downBtn.classList.add('clicked');
            }
        }
        if(vote == 0) {
            return function() {
                vote = -1;
                downvote();
                downBtn.onclick = downClick();
                upBtn.onclick = upClick();
                downBtn.classList.add('clicked');

            }

        }
        if(vote == -1) {
            return function() {
                vote = 0;
                upvote();
                downBtn.onclick = downClick();
                upBtn.onclick = upClick();
                downBtn.classList.remove('clicked');
            }
        }
    }

    function removeClass(element, className) {
        element.className = element.className
            .replace(new RegExp('(?:^|\s)'+className+'(?!\S)/'), '');
    }

})();
