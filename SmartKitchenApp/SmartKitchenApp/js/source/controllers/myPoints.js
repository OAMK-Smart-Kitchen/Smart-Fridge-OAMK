app.controller('mypoints', [
    '$scope',
    '$location',
    '$rootScope',
    '$http',
    function ($scope, $location, $rootScope, $http) {

        /*
        Stap1: functie Init
        --------------------
        */

        var init = function () {
            console.log("My Points controller started");
            processDataPoints();
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */
        

        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */

        var processDataPoints = function () {
            try {
                var newUrl = app.serviceUrl + "Exercises";
                console.log(newUrl);
                $http.get(newUrl).
                    success(function (data, status, headers, config) {
                        // this callback will be called asynchronously
                        $scope.AllExercises = data;
                    }).
                    error(function (data, status, headers, config) {
                        // called asynchronously if an error occurs
                        // or server returns response with an error status.
                        console.dir("FAILED: Data returned from AllExercises\n" + data);
                    });

            } catch (e) {
                console.log("FAILED Catched: " + e);
            }
        };
     
        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.AllExercises = new Array();
        $scope.MyPoints = $rootScope.activeMember.GamePoints;

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.DoExercise = function(id) {
            try {
                $scope.currentVideo = $scope.AllExercises[id];
                // This code loads the IFrame Player API code asynchronously.
                var tag = document.createElement('script');

                tag.src = "https://www.youtube.com/iframe_api";
                var firstScriptTag = document.getElementsByTagName('script')[0];
                firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);
                console.log("Before YT method");
                //    This function creates an <iframe> (and YouTube player)
                //    after the API code downloads.
                var player;
                window.onYouTubeIframeAPIReady = function () {
                    console.log("inYoutubeMethod");

                    player = new YT.Player('youtubePlayer', {
                        videoId: $scope.currentVideo.Url,
                        width: 868,
                        height: 488,
                        playerVars: {
                            'autoplay': 1,
                            'controls': 0,
                            'start': $scope.currentVideo.StartSeconds,
                            'end': $scope.currentVideo.StopSeconds,
                            'disablekb': 1,
                            'color': 'white'
                        },
                        events: {
                            'onReady': onPlayerReady,
                            'onStateChange': onPlayerStateChange,
                        }
                    });

                }

                bootbox.dialog({
                    closeButton: false,
                    title: "Your exercise!",
                    message: '<div id="youtubePlayer"></div>',
                    size: "large",
                    buttons: {
                        danger: {
                            label: "Stop Exercise",
                            className: "btn-default"
                        }
                    }
                });

                // 4. The API will call this function when the video player is ready.
                function onPlayerReady(event) {
                    event.target.setVolume(100);
                    event.target.playVideo();
                }

                // 5. The API calls this function when the player's state changes.
                //    The function indicates that when playing a video (state=1),
                function onPlayerStateChange(event) {
                    if (event.data == YT.PlayerState.ENDED) {
                        bootbox.hideAll();
                        bootbox.alert("Video Done!");
                    }
                }
                function stopVideo() {
                    player.stopVideo();
                }
                
            } catch (e) {
                console.log("Error: " + e);
            }
        };
       
        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);
