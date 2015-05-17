app.controller('myprofile', [
    '$scope',
    '$rootScope',
    'memberservice',
    function ($scope, $rootScope, memberservice) {

        /*
        Stap1: functie Init
        --------------------
        */

        var init = function () {
            console.log("myprofile controller started");
            showLengthWeight();
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */

        var showLengthWeight = function () {
            if ($scope.editedMember.MemberLength.length > 0) {
                $scope.lastLength = $scope.editedMember.MemberLength[$scope.editedMember.MemberLength.length - 1].Value;
            } else {
                $scope.lastLength = "XXX";
            }
            if ($scope.editedMember.MemberWeight.length > 0) {
                $scope.lastWeight = $scope.editedMember.MemberWeight[$scope.editedMember.MemberWeight.length - 1].Value;
            } else {
                $scope.lastWeight = "XX";
            }
        };

        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */

        var saveValue = function (type, value) {
            try {
                var tempdata = new Date();
                var date = tempdata.getTime();
                var success = false;
                if (type == "Length") {
                    //Save in the local active member
                    $rootScope.activeMember.MemberLength.push({ 'Value': value, 'Date': date });
                    //Send to API
                    bootbox.hideAll();
                    bootbox.dialog({
                        title: "Work in progress!",
                        closeButton: false,
                        message: '<div class="text-center" style="margin:auto;"><h4><b>We\'re updating your account... </b></h4><br /><i class="fa fa-cog fa-spin fa-3x"></i></div>"'
                    });
                    memberservice.addMemberLength({
                        'id': $rootScope.activeMember.Id,
                        'Value': value,
                        'Date': date
                    })
                 .$promise
                        .then(function onSuccess(data) {
                            console.log("Data sended succesfully");
                            success = true;
                            // Data stored successfull
                            bootbox.hideAll();
                            bootbox.dialog({
                                title: "<h1 class='text-center'>Hooray!!</h1>",
                                message: "<h2 class='text-center'><i class='fa fa-thumbs-o-up'></i>&nbsp; Your profile has been updated successfully.</h2>",
                                buttons: {
                                    success: {
                                        label: "Thanks!",
                                        className: "btn-success"
                                    }
                                }
                            });
                        }, function onFail(data) {
                            // Something went wrong
                            console.log("FAILED: Data Return:");
                            bootbox.hideAll();
                            bootbox.alert("Something went wrong... Please try again later.");
                        });
                } else if (type == "Weight") {
                    //Save in the local active member
                    $rootScope.activeMember.MemberWeight.push({ 'Value': value, 'Date': date });
                    //Send to API
                    bootbox.hideAll();
                    bootbox.dialog({
                        title: "Work in progress!",
                        closeButton: false,
                        message: '<div class="text-center" style="margin:auto;"><h4><b>We\'re updating your account... </b></h4><br /><i class="fa fa-cog fa-spin fa-3x"></i></div>"'
                    });
                    memberservice.addMemberWeight({
                        'id': $rootScope.activeMember.Id,
                        'Value': value,
                        'Date': date
                    })
                 .$promise
                        .then(function onSuccess(data) {
                            success = true;
                            console.log("Data sended succesfully");
                            // Data stored successfull
                            bootbox.hideAll();
                            bootbox.dialog({
                                title: "<h1 class='text-center'>Hooray!!</h1>",
                                message: "<h2 class='text-center'><i class='fa fa-thumbs-o-up'></i>&nbsp; Your profile has been updated successfully.</h2>",
                                buttons: {
                                    success: {
                                        label: "Thanks!",
                                        className: "btn-success"
                                    }
                                }
                            });
                        }, function onFail(data) {
                            // Something went wrong
                            console.log("FAILED: Data Return:");
                            bootbox.hideAll();
                            bootbox.alert("Something went wrong... Please try again later.");
                        });
                }
                //Save in the local memberlist
                if (success) {
                    console.log("Success save to allmembers");
                    for (var i in $scope.allMembers) {
                        if ($scope.allMembers[i].Id == $rootScope.activeMember.Id) {
                            $scope.allMembers[i] = $rootScope.activeMember;
                            break; //Stop this loop, we found it!
                        }
                    }
                }
            } catch (e) {
                bootbox.hideAll();
                bootbox.alert("Something went wrong... Please try again later.");
            }

            console.dir($scope.allMembers);
            showLengthWeight();
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.editedMember = new app.Member(); //$rootScope.activeMember
        $scope.editedMember = $rootScope.activeMember;
        $scope.editedMember.GameActivated = "true";
        $scope.editStatus = "0";
        $scope.lastWeight = "";
        $scope.lastLength = "";

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.editProfile = function (isValid) {
            if (isValid) {
                $scope.editStatus = "1";
                console.log("New credentials:");
                console.dir($scope.editedMember);
                // Save the new member information and push to server
                $rootScope.activeMember = $scope.editedMember;
                memberservice.updateProfile({
                    'id': $scope.editedMember.Id,
                    'Firstname': $scope.editedMember.Firstname,
                    'Lastname': $scope.editedMember.Lastname,
                    'DateOfBirth': $scope.editedMember.DateOfBirth,
                    'Email': $scope.editedMember.Email,
                    'Active': $scope.editedMember.Active,
                    'DefaultColor': $scope.editedMember.DefaultColor,
                    'GameActivated': $scope.editedMember.GameActivated,
                    'GamePoints': $scope.editedMember.GamePoints,
                    'Gender': $scope.editedMember.Gender,
                    'AgeCategory': $scope.editedMember.AgeCategory
            })
                 .$promise
                        .then(function onSuccess(data) {
                            // Update list of all members
                            for (var i in $scope.allMembers) {
                                if ($scope.allMembers[i].Id == $scope.editedMember.Id) {
                                    $scope.allMembers[i] = $scope.editedMember;
                                    break; //Stop this loop, we found it!
                                }
                            }
                            // Data stored successfull
                            $scope.editStatus = "0";
                            showLengthWeight();
                            bootbox.hideAll();
                            bootbox.dialog({
                                title: "<h1 class='text-center'>Hooray!!</h1>",
                                message: "<h2 class='text-center'><i class='fa fa-thumbs-o-up'></i>&nbsp; Your profile has been updated successfully.</h2>",
                                buttons: {
                                    success: {
                                        label: "Thanks!",
                                        className: "btn-success"
                                    }
                                }
                            });
                        }, function onFail(data) {
                            // Something went wrong
                            console.log("FAILED: Data Return from Edit Members Profile");
                            bootbox.alert("Something went wrong... Please try again later.");
                        });
            }
        };

        $scope.enterMemberLength = function () {
            bootbox.prompt("Enter your length below. Use the unit centimeters (cm)", function (result) {
                if (result != null) {
                    saveValue("Length", result);
                }
            });
        };

        $scope.enterMemberWeight = function () {
            bootbox.prompt("Enter your weight below. Use the unit kilograms (KG)", function (result) {
                if (result != null) {
                    saveValue("Weight", result);
                }
            });
        };

        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);