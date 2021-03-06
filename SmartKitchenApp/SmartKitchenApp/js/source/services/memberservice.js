﻿app.service('memberservice', [
    '$resource',
    function ($resource) {
        var MemberService = $resource(app.serviceUrl, { id: '@id' }, {
            Login: {
                url: app.serviceUrl + 'Kitchen/Login',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Email: '@email',
                    Password: '@password',
                }
            },
            Register: {
                url: app.serviceUrl + 'Kitchen/Register',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    KitchenName: '@kitchenname',
                    Firstname: '@firstname',
                    Lastname: '@lastname',
                    DateOfBirth: '@dateofbirth',
                    Email: '@email',
                    Password: '@password',
                    Active: '@active',
                    Admin: '@admin',
                    Gender: '@gender',
                    AgeCategory: '@agecategory'
                }
            },
            AddMember: {
                url: app.serviceUrl + 'Kitchen/Member/:id', //id from the kitchen where it should be stored.
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Firstname: '@firstname',
                    Lastname: '@lastname',
                    DateOfBirth: '@dateofbirth',
                    Email: '@email',
                    Password: '@password',
                    Active: '@active',
                    Admin: '@admin',
                    Gender: '@gender',
                    AgeCategory: '@agecategory'
                }
            },
            UpdateProfile: {
                url: app.serviceUrl + 'Member/Profile/:id', //id from the member where it should be stored.
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Firstname: '@firstname',
                    Lastname: '@lastname',
                    DateOfBirth: '@dateofbirth',
                    Email: '@email',
                    DefaultColor: '@defaultcolor',
                    Active: '@active',
                    GameActivated: '@gameactivated',
                    GamePoints: '@gamepoints',
                    Gender: '@gender',
                    AgeCategory: '@agecategory'
                }
            },
            AddMemberLength: {
                url: app.serviceUrl + 'Member/Length/:id', //id from the member where it should be stored.
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Value: '@value',
                    Date: '@date'
                }
            },
            AddMemberWeight: {
                url: app.serviceUrl + 'Member/Weight/:id', //id from the member where it should be stored.
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Value: '@value',
                    Date: '@date'
                }
            },
            ForgotPassword: {
                url: app.serviceUrl + 'Members/ForgotPassword',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    data: '@member'
                }
            }

        }
        );

        var API = {
            memberLogin: MemberService.Login,
            memberRegister: MemberService.Register,
            addMember: MemberService.AddMember,
            updateProfile: MemberService.UpdateProfile,
            addMemberLength: MemberService.AddMemberLength,
            addMemberWeight: MemberService.AddMemberWeight,
            memberForgotPassword: MemberService.ForgotPassword
        };

        return API;
    }
]);